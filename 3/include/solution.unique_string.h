class Solution {
 public:
  int lengthOfLongestSubstring(std::string s) {
    size_t maxPlaylistLength = 0;
    int songPos[128];
    for (int i = 0; i < 128; i++) {
      songPos[i] = -1;
    }
    std::string uniquePlaylist;

    for (size_t i = 0; i < s.length(); i++) {
      const char song = s[i];
      if (songPos[song] == -1) {
        // Unique song, join our playlist!
        songPos[song] = uniquePlaylist.length();
        uniquePlaylist += song;
      } else {
        // Sorry the song is in the playlist, we have to cut the playlist at
        // some point, for example:
        // (a, b, c) + b*
        const int oldPos = songPos[song];  // 1
        // (a, b, c) + b* ->
        // (a, b)
        const std::string deletedSongs = uniquePlaylist.substr(0, oldPos + 1);
        // (a, b, c) + b* ->
        //       (c, b*)
        const std::string newPlaylist =
            uniquePlaylist.substr(oldPos + 1,
                                  uniquePlaylist.length() - oldPos - 1) +
            song;
        // Update song positions in the playlist
        // (a, b) -> delete positions
        for (const char deletedSong : deletedSongs) {
          songPos[deletedSong] = -1;
        }
        // (c, b*) -> update positions
        for (size_t j = 0; j < newPlaylist.length(); j++) {
          const char newSong = newPlaylist[j];
          songPos[newSong] = j;
        }

        uniquePlaylist = newPlaylist;
      }

      if (uniquePlaylist.length() > maxPlaylistLength) {
        maxPlaylistLength = uniquePlaylist.length();
      }
    }

    return (int)maxPlaylistLength;
  }
};
