# ImGui SFML Music Player
C++ Music Player using ImGui + SFML

Welcome to my first ever open source program! Done as part of a code test & may continue afterwards for learning imgui & SFML.

Decided to make this open source since there wasn't anything out there that used ImGui and SFML together to make a music player, thought I may as well.

This is the first time I've made anything open-source, so appologise if I haven't done something properly. I got it uploaded very early so if you want you can go checkout the awful code I began with while learning ImGui and SFML.

More About Me: http://duncanbunting.com

Feel free to message/email me if you have any questions.

---

I will not longer be using it, and instead GitHub Issues but to show where it all began here's the early development issue tracking spreadsheet i madeup: https://docs.google.com/spreadsheets/d/1c5FJh6jmOxvn2W8SCCa5x8n5d-v1SeSz_31nJoxhd5w/edit?usp=sharing

---

This project makes use of SFML 2.4.2, ImGui and Dirent. Everything is included in the repo so you don't have to set anything up.

SFML 2.4.2 : https://www.sfml-dev.org/download/sfml/2.4.2/
- Used for displaying Track Art and playing Music.
- The only problem that may occur related to SFML after cloning is missing .dll files, simply take the .dll files SFML provides in its download and place in the solution directory: http://i.imgur.com/k3pUdO9.png

ImGui : https://github.com/ocornut/imgui
- Used for the UI

ImGui SFML : https://github.com/eliasdaler/imgui-sfml


Dirent : http://softagalleria.net/dirent.php
- Used for loading files from the music folder
- This is irrelevent with C++17, the best thing to do is upgrade to C++17 and use filesystem to load the files - For now however this program uses dirent.h to load the files.

---