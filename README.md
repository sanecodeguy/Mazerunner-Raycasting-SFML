**Mazerunner: The Golden Door**

Mazerunner: The Golden Door is an exciting maze-exploration game developed using C++ and SFML. The objective is to navigate the maze, battle monsters, and find the elusive golden door to escape while avoiding death.

![image](https://github.com/user-attachments/assets/4d386ce8-4b5d-4605-b421-d8c98414067b)

**Features:**

    Thrilling Gameplay: Fight monsters and traverse the maze to find the golden door.
    Smooth Movement: Use W, A, S, D keys for navigation and the Space key to attack.
    Efficient Algorithm: The maze and game logic are powered by the DDA Algorithm, ensuring precision and performance.

**Prerequisites:**
Before downloading and running the game, ensure you have:

    A C++ compiler (e.g., g++) installed.
    SFML library installed.

**Installation Instructions**

Follow these steps to download, build, and run the game:

**Step 1: Clone the Repository**

    git clone https://github.com/yourusername/Mazerunner-Golden-Door.git
    cd Mazerunner-Golden-Door

**Step 2: Install Prerequisites**

Ensure g++ and SFML are installed:

 ** For Arch Linux **

    sudo pacman -S gcc sfml

**For Ubuntu/Debian**

    sudo apt update && sudo apt install g++ libsfml-dev

**For Mac (using Homebrew):**

    brew install gcc sfml

**Step 3: Build the Game**

Compile the game using the following command:

    g++ -std=c++17 -o main main.cpp -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

**Step 4: Run the Game**

Execute the game using:

    ./main

**License**
This project is licensed under rizzons.

Feel free to fork the repository and contribute to enhance the gameplay or add new features!

Make sure to replace yourusername in the repository link with your actual GitHub username.
