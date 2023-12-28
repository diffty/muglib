#ifdef TARGET_PSVITA
    #define sockaddrIn SceNetSockaddrIn
    #define sendto sceNetSendto
    #define socket sceNetSocket
    #define in_addr SceNetInAddr
    #define inet_pton sceNetInetPton
    #define sockaddr_in SceNetSockaddrIn
    #define htonl sceNetHtonl
    #define htons sceNetHtons
    #define printf psvDebugScreenPrintf

#endif
