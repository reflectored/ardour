/*
    Copyright (C) 2012 Paul Davis

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#ifndef __ardour_sg_rack_h__
#define __ardour_sg_rack_h__

#include <list>
#include <string>
#include <boost/shared_ptr.hpp>

#include "ardour/types.h"
#include "ardour/session_object.h"


namespace ARDOUR {

class Route;
class SoundGridPlugin;

class SoundGridRack : public SessionObject {
  public:
    SoundGridRack (Session&, Route&, const std::string& name);
    ~SoundGridRack ();
    
    void add_plugin (boost::shared_ptr<SoundGridPlugin>);
    void remove_plugin (boost::shared_ptr<SoundGridPlugin>);
    
    void set_gain (gain_t);
    void set_input_gain (gain_t);

  private:
    Route& _route;

    typedef std::list<boost::shared_ptr<SoundGridPlugin> > PluginList;
    PluginList _plugins;
};

} // namespace ARDOUR

#endif /* __ardour_sg_rack_h__ */
