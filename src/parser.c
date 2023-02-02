#include "parser.h"
#include "options.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>

#define PARSING_ERROR "PARSING ERROR"

int get_domain_name(char *result, const char *input, size_t res_len)
{
        if (!result || !input)
                return -1;

        e_debug("Parsing %s\n", input);

        memset(result, 0x00, res_len);
        char *slashes = strstr(input, "//");
        long off = (slashes != NULL) ? ((long)slashes - (long)input + 2) : (0);

        char tmp = 0;
        int i = 0;
        for (i = 0; i < res_len; i++) {
                tmp = input[off + i];
                if (tmp == '/' || tmp == ':' || tmp == 0)
                        break;

                result[i] = tmp;
        }

        if (i == res_len) {
                e_warning("Domain name was not fully parsed due to short buffer\n", NULL);
        }

        e_debug("parsed %s of %d lenght\n", result, i);
        return 0;
}

const char *get_address_family(int af)
{
        switch (af)
        {
        case AF_UNSPEC : return "Unspecified";
        case AF_LOCAL : return "Local";
        case AF_INET : return "IPv4";
        case AF_AX25 : return "Amateur Radio AX.25";
        case AF_IPX : return "Novell Internet Protocol";
        case AF_APPLETALK : return "Appletalk DDP";
        case AF_NETROM : return "Amateur radio NetROM";
        case AF_BRIDGE : return "Multiprotocol bridge";
        case AF_ATMPVC : return "ATM PVCs";
        case AF_X25 : return "Reserved for X.25 project";
        case AF_INET6: return "IPv6"; 
        case AF_ROSE: return "Amateur Radio X.25 PLP";
        case AF_DECnet: return "Reserved for DECnet project";
        case AF_NETBEUI: return "Reserved for 802.2LLC project";
        case AF_SECURITY: return "Security callback pseudo AF";
        case AF_KEY: return "PF_KEY key management API";
        case AF_NETLINK: return "Netlink";
        case AF_PACKET: return "Packet family";
        case AF_ASH: return "Ash";
        case AF_ECONET: return "Acorn Econet";
        case AF_ATMSVC: return "ATM SVCs";
        case AF_RDS: return "RDS sockets";
        case AF_SNA: return "Linux SNA Project";
        case AF_IRDA: return "IRDA sockets";
        case AF_PPPOX: return "PPPoX sockets";
        case AF_WANPIPE: return "Wanpipe API sockets";
        case AF_LLC: return "Linux LLC";
        case AF_IB: return "Native InfiniBand address";
        case AF_MPLS: return "MPLS";
        case AF_CAN: return "Controller Area Network";
        case AF_TIPC: return "TIPC sockets"; 
        case AF_BLUETOOTH: return "Bluetooth sockets";
        case AF_IUCV: return "IUCV sockets";
        case AF_RXRPC: return "RxRPC sockets";
        case AF_ISDN: return "mISDN sockets";
        case AF_PHONET: return "Phonet sockets";
        case AF_IEEE802154: return "IEEE 802.15.4 sockets";
        case AF_CAIF: return "CAIF sockets";
        case AF_ALG: return "Algorhitm sockets";
        case AF_NFC: return "NFC sockets";
        case AF_VSOCK: return "vSockets";
        case AF_KCM: return "Kernel Connection Multiplexor";
        case AF_QIPCRTR: return "Qualcomm IPC Router";
        case AF_SMC: return "SMC sockets";
        case AF_XDP: return "XDP sockets";
        case AF_MCTP: return "Management component transport protocol";
        default: break;
        }
        
        return PARSING_ERROR;
}

const char *get_protocol(int p)
{
        switch (p)
        {
        case IPPROTO_IP: return "TCP";
        case IPPROTO_ICMP: return "ICMP";
        case IPPROTO_IGMP: return "IGMP";
        case IPPROTO_IPIP: return "IPIP";
        case IPPROTO_TCP: return "TCP";
        case IPPROTO_EGP: return "EGP";
        case IPPROTO_PUP: return "PUP";
        case IPPROTO_UDP: return "UDP";
        case IPPROTO_IDP: return "IDP";
        case IPPROTO_TP: return "TP";
        case IPPROTO_DCCP: return "DCCP";
        case IPPROTO_IPV6: return "IPV6";
        case IPPROTO_RSVP: return "RSVP";
        case IPPROTO_GRE: return "GRE";
        case IPPROTO_ESP: return "ESP";
        case IPPROTO_AH: return "AH";
        case IPPROTO_MTP: return "MTP";
        case IPPROTO_BEETPH: return "BEETPH";
        case IPPROTO_ENCAP: return "ENCAP";
        case IPPROTO_PIM: return "PIM";
        case IPPROTO_COMP: return "COMP";
        case IPPROTO_SCTP: return "SCTP";
        case IPPROTO_UDPLITE: return "UDPLITE";
        case IPPROTO_MPLS: return "MPLS";
        case IPPROTO_ETHERNET: return "ETHERNET";
        case IPPROTO_RAW: return "RAW";
        case IPPROTO_MPTCP: return "MPTCP";
        default: break;
        }

        return PARSING_ERROR;
}

const char *get_socktype(int st)
{
        return PARSING_ERROR;
}
