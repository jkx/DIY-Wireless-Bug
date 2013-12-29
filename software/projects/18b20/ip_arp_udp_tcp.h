/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 * Author: Guido Socher 
 * Copyright:LGPL V2
 * See http://www.gnu.org/licenses/old-licenses/lgpl-2.0.html
 *
 * IP/ARP/UDP/TCP functions
 *
 * Chip type           : ATMEGA88/168/328/644 with ENC28J60
 *********************************************/
//@{
#ifndef IP_ARP_UDP_TCP_H
#define IP_ARP_UDP_TCP_H 1
#include "ip_config.h"
#include <avr/pgmspace.h>

// -- web server functions --
// you must call this function once before you use any of the other server functions:
extern void init_ip_arp_udp_tcp(uint8_t *mymac,uint8_t *myip,uint16_t port);
// for a UDP server:
#if defined (UDP_server)
extern uint8_t eth_type_is_ip_and_my_ip(uint8_t *buf,uint16_t len);
extern void make_udp_reply_from_request_udpdat_ready(uint8_t *buf,uint16_t datalen,uint16_t port);
extern void make_udp_reply_from_request(uint8_t *buf,char *data,uint8_t datalen,uint16_t port);
#endif
// return 0 to just continue in the packet loop and return the position 
// of the tcp data if there is tcp data part
extern uint16_t packetloop_icmp_tcp(uint8_t *buf,uint16_t plen);
// functions to fill the web pages with data:
extern uint16_t fill_tcp_data_p(uint8_t *buf,uint16_t pos, const prog_char *progmem_s);
extern uint16_t fill_tcp_data(uint8_t *buf,uint16_t pos, const char *s);
// fill a binary string of len data into the tcp packet
extern uint16_t fill_tcp_data_len(uint8_t *buf,uint16_t pos, const uint8_t *s, uint8_t len);
// send data from the web server to the client:
extern void www_server_reply(uint8_t *buf,uint16_t dlen);

// -- client functions --
#if defined (WWW_client) || defined (NTP_client) || defined (UDP_client) || defined (TCP_client) || defined (PING_client)
extern void client_set_gwip(uint8_t *gwipaddr);
// do a continues refresh until found:
extern void client_gw_arp_refresh(void);
// do an arp request once (call this function only if enc28j60PacketReceive returned zero:
extern void client_arp_whohas(uint8_t *buf,uint8_t *gwipaddr);
extern uint8_t client_waiting_gw(void); // 1 no GW mac yet, 0 have a gw mac
#endif


#if defined (WWW_client) || defined (TCP_client) 
#define client_set_wwwip client_tcp_set_serverip
// set the ip of the next tcp session that we open to a server
extern void client_tcp_set_serverip(uint8_t *ipaddr);
#endif


#ifdef TCP_client
// To use the tcp client you need to:
//
// Declare a callback function to get the result (tcp data from the server):
//
// uint8_t your_client_tcp_result_callback(uint8_t fd, uint8_t statuscode,uint16_t data_start_pos_in_buf, uint16_t len_of_data){...your code;return(close_tcp_session);}
//
// statuscode=0 means the buffer has valid data, otherwise len and pos_in_buf
// are invalid. That is: do to use data_start_pos_in_buf and len_of_data
// if statuscode!=0.
//
// This callback gives you access to the TCP data of the first
// packet returned from the server. You should aim to minimize the server
// output such that this will be the only packet.
//
// close_tcp_session=1 means close the session now. close_tcp_session=0
// read all data and leave it to the other side to close it. 
// If you connect to a web server then you want close_tcp_session=0.
// If you connect to a modbus/tcp equipment then you want close_tcp_session=1
//
// Declare a callback function to be called in order to fill in the 
//
// request (tcp data sent to the server):
// uint16_t your_client_tcp_datafill_callback(uint8_t fd){...your code;return(len_of_data_filled_in);}
//
// Now call: 
// fd=client_tcp_req(&your_client_tcp_result_callback,&your_client_tcp_datafill_callback,portnumber);
//
// fd is a file descriptor like number that you get back in the fill and result
// function so you know to which call of client_tcp_req this callback belongs.
//
// You can not start different clients (e.g modbus and web) at the
// same time but you can start them one after each other. That is
// when the request has timed out or when the result_callback was
// executed then you can start a new one. The fd makes it still possible to
// distinguish in the callback code the different types you started.
//
// Note that you might never get called back if the other side does
// not answer. A timer would be needed to recongnize such a condition.
//
// We use callback functions because that is the best implementation
// given the fact that we have very little RAM memory.
//
extern uint8_t client_tcp_req(uint8_t (*result_callback)(uint8_t fd,uint8_t statuscode,uint16_t data_start_pos_in_buf, uint16_t len_of_data),uint16_t (*datafill_callback)(uint8_t fd),uint16_t port);
#endif

#ifdef WWW_client
// ----- http get
extern void client_browse_url(prog_char *urlbuf, char *urlbuf_varpart, prog_char *hoststr,void (*callback)(uint8_t,uint16_t,uint16_t));
// The callback is a reference to a function which must look like this:
// void browserresult_callback(uint8_t statuscode,uint16_t datapos,uint16_t len)
// statuscode=0 means a good webpage was received, with http code 200 OK
// statuscode=1 an http error was received
// any other statuscode means the other side in not a web server and in this case datapos is also zero
// ----- http post
// client web browser using http POST operation:
// additionalheaderline must be set to NULL if not used.
// postval is a string buffer which can only be de-allocated by the caller 
// when the post operation was really done (e.g when callback was executed).
// postval must be urlencoded.
extern void client_http_post(prog_char *urlbuf, prog_char *hoststr, prog_char *additionalheaderline,char *postval,void (*callback)(uint8_t,uint16_t,uint16_t));
// The callback is a reference to a function which must look like this:
// void browserresult_callback(uint8_t statuscode,uint16_t datapos,uint16_t len)
// statuscode=0 means a good webpage was received, with http code 200 OK
// statuscode=1 an http error was received
// any other statuscode means the other side in not a web server and in this case datapos is also zero
#endif

#ifdef NTP_client
// be careful to not mix client_ntp_request with situations where you are filling
// a web-page. Normally you will be using the same packet buffer and
// client_ntp_request writes immediately to buf. You might need to
// set a marker and call client_ntp_request when your main loop is idle.
extern void client_ntp_request(uint8_t *buf,uint8_t *ntpip,uint8_t srcport);
extern uint8_t client_ntp_process_answer(uint8_t *buf,uint32_t *time,uint8_t dstport_l);
#endif

#ifdef UDP_client
// There are two ways of using this UDP client:
//
// 1) you call send_udp_prepare, you fill the data yourself into buf starting at buf[UDP_DATA_P], 
// you send the packet by calling send_udp_transmit
//
// 2) You just allocate a large enough buffer for you data and you call send_udp and nothing else
// needs to be done.
//
extern void send_udp_prepare(uint8_t *buf,uint16_t sport, uint8_t *dip, uint16_t dport);
extern void send_udp_transmit(uint8_t *buf,uint8_t datalen);

// send_udp sends via gwip, you must call client_set_gwip at startup, datalen must be less than 220 bytes
extern void send_udp(uint8_t *buf,char *data,uint8_t datalen,uint16_t sport, uint8_t *dip, uint16_t dport);
#endif

// you can find out who ping-ed you if you want:
extern void register_ping_rec_callback(void (*callback)(uint8_t *srcip));

#ifdef PING_client
extern void client_icmp_request(uint8_t *buf,uint8_t *destip);
// you must loop over this function to check if there was a ping reply:
extern uint8_t packetloop_icmp_checkreply(uint8_t *buf,uint8_t *ip_monitoredhost);
#endif // PING_client

#ifdef WOL_client
extern void send_wol(uint8_t *buf,uint8_t *wolmac);
#endif // WOL_client

#if defined GRATARP
// send a Gratuitous arp, this is to refresh the arp
// cash of routers and switches. It can improve the response
// time in wifi networks as some wifi equipment expects the initial
// communication to not start from the network side. That is wrong
// but some consumer devices are made like this.
extern uint8_t gratutious_arp(uint8_t *buf);
#endif // GRATARP

//
#endif /* IP_ARP_UDP_TCP_H */
//@}
