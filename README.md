# 🎵 Console-based Wynk Music App 🎵

This project was completed during the 3rd semester for the Data Structures and Algorithms (DSA) course. The goal was to simulate the functionalities of the Wynk music app using C programming language and various data structures.

## Features 🚀

The simulated Wynk music app includes the following features:

- **User Management:** 
  - ✍️ Sign up
  - 🔑 Log in
  - 🧑‍💼 View user details

- **Music Management:**
  - 🎶 Browse songs
  - 📂 Create and manage playlists
  - ▶️ Play songs
  - 🔍 Search for songs

## Data Structures Used 📊

- **Linked Lists:** Used to manage playlists and song queues.
- **Hash Tables:** Implemented for efficient user management and song searches.
- **Stacks:** Utilized for the "recently played" feature.
- **Queues:** Employed for handling song playback order.
  
## Files Included 📁

- `main.c`: The main source code file containing the core functionality.
- `wynk.c`: Additional source code with supporting functions.
- `playlist.txt`: Sample data file containing playlist information.
- `songs.txt`: Sample data file with song details.
- `users.txt`: Sample data file with user information.
- `pthread_unistd.h`: Header file for thread management.
- `main.exe`: Compiled executable file for the project (Windows).

## How to Run 🛠️

1. **Compile the Source Code:**
   ```bash
   gcc main.c wynk.c -o wynk_music_app -lpthread

2. **Run the Application:**
   ```bash
   ./wynk_music_app

## Sample Usage 📖

1. **Sign Up:**
   - ✍️ Enter your details to create a new user account.

2. **Log In:**
   - 🔑 Use your credentials to log in to the app.

3. **Browse Songs:**
   - 🎶 View the list of available songs.

4. **Create Playlist:**
   - 📂 Add songs to your personalized playlist.

5. **Play Songs:**
   - ▶️ Select and play songs from the playlist or library.

6. **Search Songs:**
   - 🔍 Use the search feature to find specific songs quickly.
