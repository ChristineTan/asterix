/*
 *  Copyright (c) 2013 Croatia Control Ltd. (www.crocontrol.hr)
 *
 *  This file is part of Asterix.
 *
 *  Asterix is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Asterix is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Asterix.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * AUTHORS: Damir Salantic, Croatia Control Ltd.
 *
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#include "../main/asterix.h"
#include "asterixformat.hxx"
#include "asterixrawsubformat.hxx"
#include "asterixpcapsubformat.hxx"
#include "asterixtxtsubformat.hxx"
#include "asterixoutsubformat.hxx"
#include "asterixkmlsubformat.hxx"
#include "asterixxidefsubformat.hxx"
#include "asterixtrackssubformat.hxx"
#include "asterixfinalsubformat.hxx"
#include "asterixformatdescriptor.hxx"
#include "asterixhdlcsubformat.hxx"

#include "Tracer.h"
#include "XMLParser.h"

// Supported Asterix format names
const char* CAsterixFormat::_FormatName[CAsterixFormat::ETotalFormats] =
{
  "ASTERIX_RAW",
  "ASTERIX_PCAP",
  "ASTERIX_TXT",
  "ASTERIX_KML",
  "ASTERIX_TRACKS",
  "ASTERIX_FINAL",
  "ASTERIX_XIDEF",
  "ASTERIX_HDLC",
  "ASTERIX_ORADIS_RAW",
  "ASTERIX_ORADIS_PCAP",
  "ASTERIX_OUT",
};

//CBaseFormatDescriptor* CAsterixFormat::m_pFormatDescriptor = NULL;


bool CAsterixFormat::ReadPacket(CBaseFormatDescriptor& formatDescriptor, CBaseDevice &device, const unsigned int formatType, bool &discard)
{
  switch (formatType)
  {
      case ERaw:
          return CAsterixRawSubformat::ReadPacket(formatDescriptor, device, discard);
      case EPcap:
          return CAsterixPcapSubformat::ReadPacket(formatDescriptor, device, discard);
      case EOradisRaw:
          return CAsterixRawSubformat::ReadPacket(formatDescriptor, device, discard, true);
      case EOradisPcap:
          return CAsterixPcapSubformat::ReadPacket(formatDescriptor, device, discard, true);
      case EFinal:
          return CAsterixFinalSubformat::ReadPacket(formatDescriptor, device, discard);
      case EXIDEF:
          //todo return CAsterixXIDEFSubformat::ReadPacket(formatDescriptor, device, discard);
          return false;
      case EHDLC:
          return CAsterixHDLCSubformat::ReadPacket(formatDescriptor, device, discard);
      default:
          ASSERT(0);
  }
  LOGERROR(1, "Unsupported format type %d.\n", formatType);
  return false;
}

bool CAsterixFormat::WritePacket(CBaseFormatDescriptor& formatDescriptor, CBaseDevice &device, const unsigned int formatType, bool &discard)
{
  switch (formatType)
  {
      case ERaw:
          return CAsterixRawSubformat::WritePacket(formatDescriptor, device, discard); //TODO
      case EPcap:
          return CAsterixPcapSubformat::WritePacket(formatDescriptor, device, discard);//TODO
      case EOradisRaw:
          return CAsterixRawSubformat::WritePacket(formatDescriptor, device, discard, true); //TODO
      case EOradisPcap:
          return CAsterixPcapSubformat::WritePacket(formatDescriptor, device, discard, true);//TODO
      case ETxt:
        return CAsterixTxtSubformat::WritePacket(formatDescriptor, device, discard);
      case EKml:
        return CAsterixKmlSubformat::WritePacket(formatDescriptor, device, discard);
      case ETracks:
       return CAsterixTracksSubformat::WritePacket(formatDescriptor, device, discard);
      case EFinal:
        return CAsterixFinalSubformat::WritePacket(formatDescriptor, device, discard); // TODO
      case EXIDEF:
        return CAsterixXIDEFSubformat::WritePacket(formatDescriptor, device, discard);
      case EHDLC:
          return CAsterixHDLCSubformat::WritePacket(formatDescriptor, device, discard);//TODO
      case EOut:
        return CAsterixOutSubformat::WritePacket(formatDescriptor, device, discard);
      default:
          ASSERT(0);
  }
  LOGERROR(1, "Unsupported format type %d.\n", formatType);
  return false;
}


bool CAsterixFormat::ProcessPacket(CBaseFormatDescriptor& formatDescriptor, CBaseDevice &device, const unsigned int formatType, bool &discard)
{
  discard = false;

  switch (formatType)
  {
      case ERaw:
          return CAsterixRawSubformat::ProcessPacket(formatDescriptor, device, discard);
      case EPcap:
          return CAsterixPcapSubformat::ProcessPacket(formatDescriptor, device, discard);
      case EOradisRaw:
          return CAsterixRawSubformat::ProcessPacket(formatDescriptor, device, discard, true);
      case EOradisPcap:
          return CAsterixPcapSubformat::ProcessPacket(formatDescriptor, device, discard, true);
      case ETxt:
          return false;
      case EKml:
          return false;
      case ETracks:
          return false;
      case EFinal:
        return CAsterixFinalSubformat::ProcessPacket(formatDescriptor, device, discard);
      case EXIDEF:
        return false;
      case EHDLC:
        return CAsterixHDLCSubformat::ProcessPacket(formatDescriptor, device, discard);
      case EOut:
          return false;
      default:
          ASSERT(0);
  }
  LOGERROR(1, "Unsupported format type %d.\n", formatType);
  return false;
}

bool CAsterixFormat::HeartbeatProcessing(
    CBaseFormatDescriptor& formatDescriptor,
    CBaseDevice &device,
    const unsigned int formatType)
{
    switch (formatType)
    {
    case ERaw:
        return CAsterixRawSubformat::Heartbeat(formatDescriptor, device);
    case EPcap:
        return CAsterixPcapSubformat::Heartbeat(formatDescriptor, device);
    case EOradisRaw:
        return CAsterixRawSubformat::Heartbeat(formatDescriptor, device, true);
    case EOradisPcap:
        return CAsterixPcapSubformat::Heartbeat(formatDescriptor, device, true);
    case ETxt:
        return false;
    case EKml:
        return false;
    case ETracks:
        return CAsterixTracksSubformat::Heartbeat(formatDescriptor, device);
    case EFinal:
        return CAsterixFinalSubformat::Heartbeat(formatDescriptor, device);
    case EXIDEF:
        return false;
    case EHDLC:
        return CAsterixHDLCSubformat::Heartbeat(formatDescriptor, device);
    case EOut:
        return false;
    default:
        ASSERT(0);
    }
    LOGERROR(1, "Unsupported format type %d.\n", formatType);
    return false;
}

static void debug_trace(char const*format, ...)
{
  char buffer[1024];
  va_list args;
  va_start (args, format);
  vsprintf (buffer,format, args);
  va_end (args);
  strcat(buffer, "\n");
  LOGERROR(1, buffer);
}

CBaseFormatDescriptor* CAsterixFormat::CreateFormatDescriptor
    (const unsigned int formatType, const char* sFormatDescriptor)
{
  if (!m_pFormatDescriptor)
  {
	  char inputFile[256];

	  Tracer::Configure(debug_trace);

	  // initialize Fulliautomatix engine
	  AsterixDefinition* pDefinition = new AsterixDefinition();

	  // open asterix.ini file
	  FILE* fpini = fopen(gAsterixDefinitionsFile, "rt");
	  if (!fpini)
	  {
		LOGERROR(1, "Failed to open definitions file");
		return NULL;
	  }

	  // extract ini file path
	  std::string strInifile = gAsterixDefinitionsFile;
	  std::string strInifilePath;
		int index = strInifile.find_last_of('\\');
	    if (index < 0)
	    	index = strInifile.find_last_of('/');
	    if (index > 0)
	    {
	    	strInifilePath = strInifile.substr(0, index+1);
	    }

	  while(fgets(inputFile, sizeof(inputFile), fpini))
	  {
		std::string strInputFile;

		// remove trailing /n from filename
		int lastChar = strlen(inputFile)-1;
		while (lastChar>=0 && (inputFile[lastChar] == '\r' || inputFile[lastChar] == '\n'))
		{
		  inputFile[lastChar] = 0;
		  lastChar--;
		}
		if (lastChar <= 0)
		  continue;

		strInputFile = inputFile;

		FILE* fp = fopen(strInputFile.c_str(), "rt");
		if (!fp)
		{
			// try in folder where is ini file
			if (!strInifilePath.empty())
			{
				std::string strfilepath = strInifilePath + strInputFile;
				fp = fopen(strfilepath.c_str(), "rt");
			}

			if (!fp)
			{
			  LOGERROR(1, "Failed to open definitions file: %s\n", inputFile);
			  continue;
			}
		}

		// parse format file
		XMLParser Parser;
		if (!Parser.Parse(fp, pDefinition))
		{
		  LOGERROR(1, "Failed to parse definitions file: %s\n", strInputFile.c_str());
		}

		fclose(fp);
	  };

	  fclose(fpini);

	  m_pFormatDescriptor = new CAsterixFormatDescriptor(pDefinition);
  }
  return m_pFormatDescriptor;
}


bool CAsterixFormat::GetFormatNo(const char *formatName, unsigned int &formatType)
{
  bool found = false;
  unsigned int i;

  for (i=0; (i<ETotalFormats) && (!found); i++)
  {
      ASSERT(formatName);
      if (strcasecmp(formatName, CAsterixFormat::_FormatName[i]) == 0)
      {
          found = true;
          formatType = i;
      }
  }

  return found;
}

int CAsterixFormat::GetStatus(CBaseDevice &device, const unsigned int formatType, int query)
{
	if (device.IsOpened() == false)
		return STS_NO_DATA;

  return 0;
}



bool CAsterixFormat::OnResetInputChannel(CBaseFormatDescriptor& formatDescriptor)
{
  return false;
}


bool CAsterixFormat::OnResetOutputChannel(unsigned int channel, CBaseFormatDescriptor& formatDescriptor)
{
  return true;
}




