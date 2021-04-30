class Solution {
 public:
  int lengthOfLongestSubstring(std::string songList) {
    int maxPlaylistLength = 0;
    int songPos[128];
    for (int i = 0; i < 128; i++) {
      songPos[i] = -1;
    }
    int start = 0;

    for (int i = 0; i < (int)songList.length(); i++) {
      const char song = songList[i];
      if (songPos[song] < start) {
        // Unique song, join our playlist!
        // Scenario 1: new song in not in songPos
        // (a, b) + c*
        //  ^ start = 0
        // songPos[c] = -1
        //
        // Scenario 2: new song is in songPos but less than start position
        // (a, b, c, b*) + a*
        //        ^ start = 2
        // songPos[a] = 0
      } else {
        // Sorry the song is already in the playlist
        // We move the start position to remove all the songs on the left-hand
        // side
        // (a, b, c) + b*
        //  ^ start = 0
        // songPos[b] = 1
        // ->
        //        ^ start = 2
        const int oldSongPos = songPos[song];
        start = oldSongPos + 1;
      }

      // Update the position of the new song
      songPos[song] = i;

      // Check if the new playlist is longer
      // (a, b, c)
      //     ^ start = 1
      //        ^ i  = 2
      const int numSongsInPlaylist = i - start + 1;
      if (numSongsInPlaylist > maxPlaylistLength) {
        maxPlaylistLength = numSongsInPlaylist;
      }
    }

    return (int)maxPlaylistLength;
  }
};
