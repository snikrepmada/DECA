#include "terasic_includes.h"
#include "mem_verify.h"



bool TMEM_Verify(alt_u32 BaseAddr, alt_u32 ByteLen, alt_u32 InitValue, bool bShowMessage){
    bool bPass = TRUE;
    alt_u32 szData[1025];
    alt_u32 szRead[1025];
    int i, nRemainedLen, nAccessLen;
    alt_u32 *pDes, *pSrc, nItemNum, nPos;

    int nProgressIndex=0;
    alt_u32 szProgress[10];
    
    for(i=0;i<10;i++){
        szProgress[i] = ByteLen/10*(i+1);     
    }
    
    
    
    nItemNum = sizeof(szData)/sizeof(szData[0]);
    for(i=0;i<nItemNum;i++){
        if (i == 0)
            szData[i] = InitValue;
        else     
            szData[i] = szData[i-1] * 13;
    }
    szData[nItemNum-1] = 0xAAAAAAAA;
    szData[nItemNum-2] = 0x55555555;
    szData[nItemNum-3] = 0x00000000;
    szData[nItemNum-4] = 0xFFFFFFFF;
    
    if (bShowMessage)
        printf("write...\n");
    // write
    pDes = (alt_u32 *)BaseAddr;
    nAccessLen = sizeof(szData);
    nPos = 0;
    while(nPos < ByteLen){
        nRemainedLen = ByteLen - nPos;
        if (nAccessLen > nRemainedLen)
            nAccessLen = nRemainedLen;
        memcpy(pDes, szData, nAccessLen);
        pDes += nAccessLen/4;
        nPos += nAccessLen;
        
        if (bShowMessage){
            if (nProgressIndex <= 9 && nPos >= szProgress[nProgressIndex]){
                nProgressIndex++;
                printf("%02d%% ", nProgressIndex*10);
                usleep(50);
            }
        }            
    } 
    
    alt_dcache_flush_all();
    
    if (bShowMessage){
        nProgressIndex = 0;
        printf("\nread/verify...\n");
        usleep(50);
    }        
    
    // read & verify
    pSrc = (alt_u32 *)BaseAddr;
    nAccessLen = sizeof(szRead);
    nPos = 0;
    while(bPass && nPos < ByteLen){
        nRemainedLen = ByteLen - nPos;
        if (nAccessLen > nRemainedLen)
            nAccessLen = nRemainedLen;
       // memset(szRead, 0xAA, nAccessLen); // reset content    
        memcpy(szRead, pSrc, nAccessLen);
        // verify
        nItemNum = nAccessLen / 4;
        for(i=0;i<nItemNum && bPass;i++){
            if (szRead[i] != szData[i]){
                if (bShowMessage){
                   printf("verify ng, read=%08Xh, expected=%08Xh, i=%Xh\n", (int)szRead[i], (int)szData[i], (int)(nPos/4+i));
                   usleep(50);
                }   
                bPass = FALSE;
            }    
        }
        //
        pSrc += nItemNum;
        nPos += nAccessLen;

        if (bShowMessage){
            if (nProgressIndex <= 9 && nPos >= szProgress[nProgressIndex]){
                nProgressIndex++;
                printf("%02d%% ", nProgressIndex*10);
                usleep(50);
            }
        }            
    }     
    
    if (bShowMessage)
        printf("\n");
   
    
    return bPass;
}

bool TMEM_QuickVerify(alt_u32 BaseAddr, alt_u32 DataSize, alt_u32 DataWidth, alt_u32 AddrWidth){
    bool bPass = TRUE;
    const alt_u32 TestNum = 1024*512;
    const alt_u32 TestPattern = 0xAA;
    alt_u32 mask, Read32, Addr32, TestData32, TestAddr32;
    int i;
    
    //alt_u32 *pMem = (alt_u32 *)BaseAddr;
    // test address line
    mask = 0x01;
    for(i=0;i<AddrWidth && bPass;i++){
        //*(pMem + mask) = TestPattern;
        IOWR(BaseAddr, mask, TestPattern);
        //if (*(pMem + mask) != TestPattern)
        Read32 = IORD(BaseAddr, mask);
        if (Read32 != TestPattern)
            bPass = FALSE;
        mask <<= 1;    
    }
    
    // test data line
    mask = 0x01;
    for(i=0;i<DataWidth && bPass;i++){
        //*(pMem+i/32) = mask;
        Addr32 = i*13;
        IOWR(BaseAddr, Addr32, mask);
        Read32 = IORD(BaseAddr, Addr32);
        //if (*(pMem+i/32) != mask)
        if (Read32 != mask)
            bPass = FALSE;
        mask <<= 1;
        if (mask == 0x00)
            mask = 0x01;    
    }
    
    // random data test
    srand(alt_nticks());
    for(i=0;i<TestNum && bPass;i++){
        TestAddr32 = rand()%(DataSize/4);
        TestData32 = rand();
        IOWR(BaseAddr, TestAddr32, TestData32);
        Read32 = IORD(BaseAddr, TestAddr32);
        if (Read32 != TestData32)
            bPass = FALSE;        
        
    }
    
    return bPass;
}
