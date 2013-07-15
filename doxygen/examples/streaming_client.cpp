/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * Copyright (C) 2010 Simon Newton
 */
#include <ola/DmxBuffer.h>
#include <ola/io/SelectServer.h>
#include <ola/Logging.h>
#include <ola/OlaClientWrapper.h>
#include <ola/Callback.h>

using std::cout;
using std::endl;

bool SendData(ola::OlaCallbackClientWrapper *wrapper) {
  static unsigned int universe = 1;
  static unsigned int i = 0;
  ola::DmxBuffer buffer;
  buffer.Blackout();
  buffer.SetChannel(0, i);
  wrapper->GetClient()->SendDmx(universe, buffer);

  if (++i == 100) {
    wrapper->GetSelectServer()->Terminate();
  }
  return true;
};

int main(int, char *[]) {
  ola::InitLogging(ola::OLA_LOG_WARN, ola::OLA_LOG_STDERR);
  ola::OlaCallbackClientWrapper wrapper;

  if (!wrapper.Setup()) {
    std::cerr << "Setup failed" << endl;
    exit(1);
  }

  // Create a timeout and register it with the SelectServer
  ola::io::SelectServer *ss = wrapper.GetSelectServer();
  ss->RegisterRepeatingTimeout(25, ola::NewCallback(&SendData, &wrapper));

  // Start the main loop
  ss->Run();
}
