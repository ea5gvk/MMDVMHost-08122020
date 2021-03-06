/*
 *   Copyright (C) 2020 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef	FMNetwork_H
#define	FMNetwork_H

#include "RingBuffer.h"
#include "UDPSocket.h"
#include "Timer.h"

#include <samplerate.h>

#include <cstdint>
#include <string>

class CFMNetwork {
public:
	CFMNetwork(const std::string& myAddress, unsigned int myPort, const std::string& gatewayAddress, unsigned int gatewayPort, unsigned int sampleRate, bool debug);
	~CFMNetwork();

	bool open();

	void enable(bool enabled);

	bool writeData(float* data, unsigned int nSamples);

	bool writeEOT();

	unsigned int read(float* data, unsigned int nSamples);

	void reset();

	void close();

	void clock(unsigned int ms);

private:
	CUDPSocket       m_socket;
	sockaddr_storage m_addr;
	unsigned int     m_addrLen;
	unsigned int     m_sampleRate;
	bool             m_debug;
	bool             m_enabled;
	CRingBuffer<unsigned char> m_buffer;
	CTimer           m_pollTimer;
	SRC_STATE*       m_incoming;
	SRC_STATE*       m_outgoing;

	bool writePoll();
};

#endif
