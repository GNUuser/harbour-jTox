/*
    Copyright (C) 2016 Ales Katona.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
//import org.nemomobile.notifications 1.0
import "../components"


Page {
    id: page
    allowedOrientations: Orientation.Portrait
    enabled: toxcore.status > 0

    SilicaListView {
        id: listView
        header: PageHeader {
            title: qsTr("Friend Requests")
        }

        anchors.fill: parent
        spacing: Theme.paddingLarge
        model: requestmodel
        VerticalScrollDecorator {
            flickable: listView
        }

        delegate: RequestItem {}
    }
}
