/*
 * Copyright (c) 2005, Swedish Institute of Computer Science
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack
 *
 * @(#)$Id: dhcpc.h,v 1.3 2006/06/11 21:46:37 adam Exp $
 */
#ifndef __MT_DHCPC_H__
#define __MT_DHCPC_H__

#include "uip_timer.h"
#include "xip_ovly.h"
#include "mt_uip.h"

#define STATE_INITIAL                  0
#define STATE_SEND_DIS               1
#define STATE_OFFER_RECEIVED   2
#define STATE_SEND_REQ               3
#define STATE_CONFIG_RECEIVED 4
#define STATE_CONFIG_DONE        5

#define DHCPC_SERVER_PORT       67
#define DHCPC_CLIENT_PORT       68

struct dhcpc_state {
    char state;
    UIP_UDP_CONN *conn;
    struct timer timer;
    struct timer lease_timer;
    u16_t ticks;
    const void *mac_addr;
    int mac_len;

    u8_t serverid[4];

    u16_t lease_time[2];
    u16_t ipaddr[2];
    u16_t netmask[2];
    u16_t dnsaddr[2];
    u16_t default_router[2];
};

void dhcpc_init(const void *mac_addr, int mac_len) XIP_ATTRIBUTE(".xipsec1");
void dhcpc_request(void);
void dhcpc_appcall(void);
void dhcpc_configured(const struct dhcpc_state *s)  XIP_ATTRIBUTE(".xipsec1");
void dhcpc_set_state(u8_t state);
u8_t dhcpc_get_state(void);
void handle_dhcp(void)  XIP_ATTRIBUTE(".xipsec1");
void _handle_dhcp(void) OVLY_ATTRIBUTE(".ovlysec10");
void ws_got_ip(void)   XIP_ATTRIBUTE(".xipsec1");
void ws_got_ip_fail(void)  XIP_ATTRIBUTE(".xipsec1");

#endif /* __MT_DHCPC_H__ */