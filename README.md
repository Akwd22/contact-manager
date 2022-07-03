<div id="top"></div>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <h3 align="center">Contact Manager</h3>
  <p align="center">
    <a href="#">View Demo (TODO)</a> ·
    <a href="https://github.com/Akwd22/contact-manager/releases">Get latest release</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project">About The Project</a></li>
    <li><a href="#context">Context</a></li>
    <li><a href="#built-with">Built With</a></li>
    <li><a href="#documentation">Documentation</a></li>
    <li><a href="#getting-started">Getting Started</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contributors">Contributors</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

<div align="center">
  <img src="project-image-1.png">
  <img src="project-image-2.png">
</div>
<br />

This project basic principle is simple: an application to manage a list of contacts and their interactions such as todos. This application could be used in  a company context for example.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTEXT -->
## Context

This project is an academic project realized during the **third year** of a **Bachelor** of Computer Science.
The development was done by 2 people.

<p align="right">(<a href="#top">back to top</a>)</p>

## Built With

Entire project was built with pure C++ for the business layer and [Qt](https://www.qt.io/) for the storage and UI layers. Database used is [SQLite](https://www.sqlite.org/index.html).

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- DOCUMENTATION -->
## Documentation

You can find documentation such as the requirements analysis, UML diagrams in the folder `docs`.
Moreover, Doxygen docs can be generated in HTML with script file `doxy/run_doxygen` ([Doxygen](https://doxygen.nl/) must be installed in your system).

<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow the steps:

### Prerequisites

To setup the project, you will need:
* [Qt 5.0+](https://www.qt.io/)

### Installation

1. Clone the repo:
   ```sh
   git clone https://github.com/Akwd22/contact-manager.git
   ```
2. Compile the project, you have two choices:
   - From command-line:
     ```sh
     cd src
     qmake
     make <debug|release>
     ```
     Then, go to `src/out/<debug|release>` and run `ui` executable to run the app, or `test_logic` if you want to run unit tests.
     
   - From Qt Creator: import the project file `src/main.pro` with default settings, and you should be good.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under The Unlicense. See LICENSE file for more information.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- Contributors -->
## Contributors

This project was made by:
- [Eddy D.](https://github.com/Akwd22)
- [Clément G.](https://github.com/Zoreph22)

<p align="right">(<a href="#top">back to top</a>)</p>
