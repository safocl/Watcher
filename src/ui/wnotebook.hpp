/**
 *\file wnotebook.hpp
 *\copyright GPL-3.0-or-later
 *\author safocl (megaSafocl)
 *\date 2023
 *
 * \detail \"Copyright safocl (megaSafocl) 2023\"
 This file is part of watcher.

 watcher is free software: you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation, either version 3 of the License, or any later version.

 watcher is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 more details.

 You should have received a copy of the GNU General Public License along with
 watcher. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtkmm/notebook.h>
//#include "clockentity.hpp"
//#include "timerentity.hpp"
//#include "logentity.hpp"

namespace core::ui {

class WNotebook final : public Gtk::Notebook {
private:
public:
    WNotebook();
    ~WNotebook();
};

}   // namespace core::ui
