proc get_clocks_feeding_pin { pin_name } {

    # Before step 1, perform an error check to ensure that pin_name
    # passed in to the procedure matches one and only one pin.
    # Return an error if it does not match one and only one pin.
    set pin_col [get_pins -compatibility_mode $pin_name]
    if { 0 == [get_collection_size $pin_col] } {
        return -code error "No pins match $pin_name"
    } elseif { 1 < [get_collection_size $pin_col] } {
        return -code error "$pin_name matches [get_collection_size $pin_col]\
            pins but must match only one"
    }
    
    # Initialize variables used in the procedure
    catch { array unset nodes_with_clocks }
    catch { array unset node_types }
    array set nodes_with_clocks [list]
    array set node_types [list]
    set pin_drivers [list]
    
    # Step 1. Get all clocks in the design and create a mapping from
    # the target nodes to the clocks on the target nodes

    # Iterate over each clock in the design
    foreach_in_collection clock_id [all_clocks] {

        set clock_name [get_clock_info -name $clock_id]
        set clock_target_col [get_clock_info -targets $clock_id]
        
        # Each clock is applied to nodes. Get the collection of target nodes
        foreach_in_collection target_id [get_clock_info -targets $clock_id] {

            # Associate the clock name with its target node
            set target_name [get_node_info -name $target_id]
            lappend nodes_with_clocks($target_name) $clock_name

            # Save the type of the target node for later use
            set target_type [get_node_info -type $target_id]
            set node_types($target_name) $target_type
        }
    }

    # Step 2. Get a list of nodes with clocks on them that are on the
    # fanin path to the specified pin

    # Iterate over all nodes in the mapping created in step 1
    foreach node_with_clocks [array names nodes_with_clocks] {

        # Use the type of the target node to create a type-specific
        # collection for the -through value in the get_fanins command.
        switch -exact -- $node_types($node_with_clocks) {
            "pin" {  set through_col [get_pins $node_with_clocks] }
            "port" { set through_col [get_ports $node_with_clocks] }
            "cell" { set through_col [get_cells $node_with_clocks] }
            "reg" {  set through_col [get_registers $node_with_clocks] }
				"net" {  set through_col [get_nets $node_with_clocks]}
            default { return -code error "$node_types($node_with_clocks) is not handled\
                as a fanin type by the script" }
        }

        # Get any fanins to the specified pin through the current node
        
		  ##Added this condition to remove warnings reported by timequest analyzer when
		  ##node type of selected nod is port.So when node type is port get_fanins function
		  ##won't be called and due to that timequest won't report any warnings.
		  
		  if {$node_types($node_with_clocks) != "port"} {
		  
          set fanin_col [get_fanins -clock -through $through_col $pin_name]

          # If there is at least one fanin node, the current node is on the
          # fanin path to the specified pin, so save it.
          if { 0 < [get_collection_size $fanin_col] } {
            lappend pin_drivers $node_with_clocks
          }
		  }
    }

    # Before step 3, perform an error check to ensure that at least one
    # of the nodes with clocks in the design is on the fanin path to
    # the specified pin.
    if { 0 == [llength $pin_drivers] } {
	   ## Commented below line as it stops the execution.It stops execution if clock
		## is input port of the top level design file.In that case input port name is 
		## evaluated by same method as other input ports are derived. - KA
        #return -code error "Can not find any node with clocks that drives $pin_name"
      foreach_in_collection port_id [get_fanins $pin_name] { break }
      set clock_port [get_node_info -name $port_id]
      #$post_message -type info "$clock_port going to $pin_name"		
		return $clock_port
    }  

    
    # Step 3. From the list of nodes created in step 2, find the node
    # closest to the specified pin and return the clocks on that node.

    while { 1 < [llength $pin_drivers] } {

        # Get the first two nodes in the pin_drivers list
        set node_a [lindex $pin_drivers 0]
        set node_b [lindex $pin_drivers 1]
        
        # Use the type of the target node to create a type-specific
        # collection for the -through value in the get_fanins command.
        switch -exact -- $node_types($node_b) {
            "pin" {  set through_col [get_pins $node_b] }
            "port" { set through_col [get_ports $node_b] }
            "cell" { set through_col [get_cells $node_b] }
            "reg" {  set through_col [get_registers $node_b] }
				"net" {  set_through_col [get_nets $node_b]}
            default { return -code error "$node_types($node_b) is not handled\
                as a fanin type by the script" }
        }

        # Check whether node_b is on the fanin path of node_a        
        set fanin_col [get_fanins -clock -through $through_col $node_a]

        # If there is at least one fanin node, node_b must be further
        # away from the specified pin than node_a is.
        # If there is no fanin node, node_b must be closer to the
        # specified pin than node_a is.
        if { 0 < [get_collection_size $fanin_col] } {

            # node_a is closer to the pin.
            # Remove node_b from the pin_drivers list
            set pin_drivers [lreplace $pin_drivers 1 1]

        } else {

            # node_b is closer to the pin
            # Remove node_a from the pin_drivers list
            set pin_drivers [lrange $pin_drivers 1 end]
        }
    }
    
    # The one node left in pin_drivers is the node driving the specified pin
    set node_driving_pin [lindex $pin_drivers 0]

    # Look up the clocks on the node in the mapping from step 1 and return them

    return $nodes_with_clocks($node_driving_pin)
}

proc outport_constraint {node_name ddr outclk outmax_delay outmin_delay} {
  foreach_in_collection   pin_id  [get_pins -compatibility_mode $node_name ] {
    set pin_name [get_node_info -name $pin_id]
    foreach_in_collection port_id [get_fanouts $pin_name] { 
    # assume it is only connected to one port (= pin of the FPGA)
    if {[get_node_info -type $port_id] == "port"} break 
    }
    set out_port [get_node_info -name $port_id]
    #post_message -type info "$pin_name going to $out_port"

	 if {$ddr} {
      set_output_delay -clock $outclk -max -add_delay $outmax_delay $out_port
      set_output_delay -clock $outclk -min -add_delay $outmin_delay $out_port				
		
      set_output_delay -clock $outclk -clock_fall -max -add_delay $outmax_delay $out_port
      set_output_delay -clock $outclk -clock_fall -min -add_delay $outmin_delay $out_port				
		
	 } else {
      set_output_delay -clock $outclk -max -add_delay $outmax_delay $out_port
      set_output_delay -clock $outclk -min -add_delay $outmin_delay $out_port					 
	 }	 
  }
}

proc inport_constraint {node_name ddr inclk inmax_delay inmin_delay} {
  foreach_in_collection   pin_id  [get_pins -compatibility_mode $node_name ] {
    set pin_name [get_node_info -name $pin_id]
    foreach_in_collection port_id [get_fanins $pin_name] { break }
    set in_port [get_node_info -name $port_id]
    #post_message -type info "$in_port going to $pin_name"

	 if {$ddr} {
      set_input_delay -clock $inclk -max -add_delay $inmax_delay $in_port
      set_input_delay -clock $inclk -min -add_delay $inmin_delay $in_port				
		
      set_input_delay -clock $inclk -clock_fall -max -add_delay $inmax_delay $in_port
      set_input_delay -clock $inclk -clock_fall -min -add_delay $inmin_delay $in_port				
		
	 } else {
      set_input_delay -clock $inclk -max -add_delay $inmax_delay $in_port
      set_input_delay -clock $inclk -min -add_delay $inmin_delay $in_port					 
	 }	 
  }
}

proc ioport_constraint {node_name ddr outclk outmax_delay outmin_delay inclk inmax_delay inmin_delay} {
  foreach_in_collection   pin_id  [get_pins -compatibility_mode $node_name ] {
    set pin_name [get_node_info -name $pin_id]
    foreach_in_collection port_id [get_fanouts $pin_name] { 
    # assume it is only connected to one port (= pin of the FPGA)
    if {[get_node_info -type $port_id] == "port"} break 
    }
    set io_port [get_node_info -name $port_id]
    #post_message -type info "$pin_name going to $io_port"

	 if {$ddr} {
      set_output_delay -clock $outclk -max -add_delay $outmax_delay $io_port
      set_output_delay -clock $outclk -min -add_delay $outmin_delay $io_port				
		
      set_output_delay -clock $outclk -clock_fall -max -add_delay $outmax_delay $io_port
      set_output_delay -clock $outclk -clock_fall -min -add_delay $outmin_delay $io_port	

      set_input_delay -clock  $inclk -max -add_delay $inmax_delay $io_port
      set_input_delay -clock  $inclk -min -add_delay $inmin_delay $io_port				
		
      set_input_delay -clock  $inclk -clock_fall -max -add_delay $inmax_delay $io_port
      set_input_delay -clock  $inclk -clock_fall -min -add_delay $inmin_delay $io_port		
		
	 } else {
      set_output_delay -clock $outclk -max -add_delay $outmax_delay $io_port
      set_output_delay -clock $outclk -min -add_delay $outmin_delay $io_port		
		
      set_input_delay -clock  $inclk -max -add_delay $inmax_delay $io_port
      set_input_delay -clock  $inclk -min -add_delay $inmin_delay $io_port				
		
	 }	 
  }
}

proc clk_constraint {node_name} {
  foreach_in_collection pin_id [get_pins -compatibility_mode $node_name] {    

    # pin_name has the full design hierarchy of the muxsel pin for one
    # instantiation of reusable_block
    set pin_name [get_node_info -name $pin_id]	 
    set clk  [get_clocks_feeding_pin $pin_name]
    return $clk 
  }
}

proc map_node_to_outport {node_name} {
  foreach_in_collection   pin_id  [get_pins -compatibility_mode $node_name ] {
    set pin_name [get_node_info -name $pin_id]
    foreach_in_collection port_id [get_fanouts $pin_name] { 
    # assume it is only connected to one port (= pin of the FPGA)
    if {[get_node_info -type $port_id] == "port"} break 
    }
    set outport [get_node_info -name $port_id]	
    #post_message -type info "$pin_name going to $outport"
	 return $outport

  }
}

proc map_node_to_inport {node_name} {
  foreach_in_collection   pin_id  [get_pins -compatibility_mode $node_name ] {
    set pin_name [get_node_info -name $pin_id]
	
    foreach_in_collection port_id [get_fanins $pin_name] { break }
    set inport [get_node_info -name $port_id]
    #post_message -type info "$inport going to $pin_name"		
    return $inport
  }
}

proc get_timequest_name {hier_name} {
#
# Description:  Convert the full hierarchy name into a TimeQuest name
#
# ----------------------------------------------------------------
	set sta_name ""
	for {set inst_start [string first ":" $hier_name]} {$inst_start != -1} {} {
		incr inst_start
		set inst_end [string first "|" $hier_name $inst_start]
		if {$inst_end == -1} {
			append sta_name [string range $hier_name $inst_start end]
			set inst_start -1
		} else {
			append sta_name [string range $hier_name $inst_start $inst_end]
			set inst_start [string first ":" $hier_name $inst_end]
		}
	}
	return $sta_name
}

proc get_core_full_instance_list {corename} {
#
# Description:  Get a list of all ALTMEMPHY instances (full hierarchy names)
#               in TimeQuest
#
# ----------------------------------------------------------------
	set instance_list [list]

	# Look for a keeper (register) name
	# Try mem_clk[0] to determine core instances
	set search_list [list "*"]
	set found 0
	for {set i 0} {$found == 0 && $i != [llength $search_list]} {incr i} {
		set pattern [lindex $search_list $i]
		set instance_collection [get_keepers -nowarn "*|${corename}:*|$pattern"]
		if {[get_collection_size $instance_collection] == 0} {
			set instance_collection [get_keepers "${corename}:*|$pattern"]
		}
		if {[get_collection_size $instance_collection] > 0} {
			set found 1
		}
	}
	# regexp to extract the full hierarchy path of an instance name
	set inst_regexp {(^.*}
	append inst_regexp ${corename}
	append inst_regexp {:[A-Za-z0-9\.\\_\[\]\-\$():]+)\|}
	foreach_in_collection inst $instance_collection {
		set name [get_node_info -name $inst]
		if {[regexp -- $inst_regexp $name -> hier_name] == 1} {
			if {[lsearch $instance_list [escape_brackets $hier_name]] == -1} {
				lappend instance_list $hier_name
			}
		}
	}
	return $instance_list
}


proc get_core_instance_list {corename} {
#
# Description:  Get a list of all ALTMEMPHY instances in TimeQuest
#
# ----------------------------------------------------------------
	set full_instance_list [get_core_full_instance_list $corename]
	set instance_list [list]

	foreach inst $full_instance_list {
		set sta_name [get_timequest_name $inst]
		if {[lsearch $instance_list [escape_brackets $sta_name]] == -1} {
			lappend instance_list $sta_name
		}
	}
	return $instance_list
}
