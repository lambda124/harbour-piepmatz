/*
    Copyright (C) 2017-18 Sebastian J. Wolf

    This file is part of Piepmatz.

    Piepmatz is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Piepmatz is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Piepmatz. If not, see <http://www.gnu.org/licenses/>.
*/
import QtQuick 2.0
import Sailfish.Silica 1.0
import "../pages"
import "../js/functions.js" as Functions
import "../js/twemoji.js" as Emoji

Column {
    id: tweetTextColumn
    property variant tweet;
    property bool truncateText : false;
    visible: (tweetContentText.text !== "")

    width: parent.width

    Text {
        width: parent.width
        id: tweetContentText
        text: tweetTextColumn.truncateText ? Emoji.twemoji.parse(Functions.getRelevantTweet(tweetTextColumn.tweet).full_text, { callback: function(icon, options, variant) { return '../js/emoji/' + icon + '.svg'; }, size: Theme.fontSizeSmall }) : Emoji.twemoji.parse(Functions.enhanceText(Functions.getRelevantTweet(tweetTextColumn.tweet).full_text, Functions.getRelevantTweet(tweetTextColumn.tweet).entities, Functions.getRelevantTweet(tweetTextColumn.tweet).extended_entities), { callback: function(icon, options, variant) { return '../js/emoji/' + icon + '.svg'; }, size: Theme.fontSizeSmall })
        font.pixelSize: Theme.fontSizeExtraSmall
        color: Theme.primaryColor
        elide: tweetTextColumn.truncateText ? Text.ElideRight : Text.ElideNone
        wrapMode: Text.Wrap
        textFormat: Text.StyledText
        maximumLineCount: tweetTextColumn.truncateText ? 3 : 42
        onLinkActivated: {
            Functions.handleLink(link);
        }
        linkColor: Theme.highlightColor
    }
}


