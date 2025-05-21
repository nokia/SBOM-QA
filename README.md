# SBOM QA

Testing the quality of Software Compositon Analyzis (SCA) or SBOM generator tools. SCA tools are detecting the transient
dependencies of software. The purpose of this repository is to benchmark a handfull of open souce SCA tools and check

* How complete SBOM they generate. Are all the dependencies discovered and if there are any false positives?
* What is the quality of the generated SBOM. Is the SBOM compliant with the
[OpenChain Telco SBOM Guide](https://github.com/OpenChain-Project/Telco-WG/)?

## Work method

1. We select test targets. These are software artefacts created using different technologies with a know list of
   dependencies. We create reference SBOMs for the artefacts.
2. We select SCA tools. Due to the nature of the activity we use open source SCA tools, but the methodolgy can be
   applied to any SCA tool.
3. We run the SCA tools on the test targets and compare the result to the reference SBOMs. Results are documented.

### 1. Test targets

*Note:* The Artefact links are only examples. 

| id | Description | Artefact | Reference SBOM |
| -- | ----------- | -------- | -------------- | 
| 1  | C/C++ code without package manager | [C/curl](C/curl) | TBD |
| 2  | C/C++ code without package manager | [C/git](C/git) | TBD |
| 3  | C/C++ code with Conan package manager | [C++_CONAN dependencies/CppfrontTemplate](C++_CONAN dependencies/CppfrontTemplate) | TBD |
| 4  | Go module with dependencies | [Go/Go/hugo](Go/Go/hugo) | TBD |
| 5  | Python module with dependencies | [python/fastapi](python/fastapi) | TBD |
| 6  | npm project with dependencies | [Node.js/my-new-folder1/express](Node.js/my-new-folder1/express) | TBD |
| 7  | Java project with Maven | [java_Maven/java_Maven/elasticsearch](java_Maven/java_Maven/elasticsearch) | TBD |
| 8  | Container image with apt-install, go install, wget, git clone and local copy of a zip file | [ContainerImage/ContainerImage/pggb](ContainerImage/ContainerImage/pggb) | TBD |

### 2. Selected SCA tools

| Tool | Nontes |
| ---- | ------ |


# Folder Descriptions

Descriptions of each test folder and what it contains.

## C++ Projects
This folder contains five representative C++ projects selected for testing how accurately Software Composition Analysis (SCA) tools detect dependencies, especially in environments with and without package managers.

1. godot – An advanced open-source game engine, showcasing large-scale C++ applications with complex build dependencies.

2. gpt4all – A local large language model implementation, useful for evaluating ML-related C++ dependencies.

3. llama.cpp – A lightweight C++ LLM runner, testing how well SCA tools track AI/ML-related source integrations.

4. opencv – A popular library for computer vision, included to test SCA handling of modular, widely-used libraries.

5. tensorflow (C++ part) – Although TensorFlow is mainly known for Python, its core is C++, making it ideal for testing detection in hybrid ecosystems.

## C++ with Conan Package Manager
The C++_CONAN folder includes five example projects using the Conan package manager. These test targets help evaluate how SCA tools detect and interpret dependencies when Conan is used.

1. Coronan – A sample project using Conan to manage simple C++ dependencies, ideal for testing base Conan integration.

2. CppfrontTemplate – A modern C++ project template using Cppfront, useful for verifying dependency capture in evolving C++ standards.

3. conan-center-index – The official Conan recipe index; included to test how tools treat metadata-rich repositories and package recipes.

4. conan_project_template – A minimal Conan-ready project template, good for testing SCA behavior on clean setups.

5. cpp-conan-docker-starter – Combines Conan with Docker for containerized builds, testing how tools handle hybrid environments.

## C Projects (No Package Manager)
The C folder contains five open-source projects written in C and built without a package manager. These projects are ideal for evaluating how SCA tools detect direct and transitive dependencies in traditional C environments.

1. curl – A command-line tool and library for transferring data with URLs. Useful for testing detection of HTTP and networking-related dependencies.

2. git – A distributed version control system. Included to benchmark how deeply tools can analyze large C codebases with complex build systems.

3. libgit2 – A C library for interacting with Git repositories. Enables checking dependency resolution in C libraries used by other applications.

4. sqlite – A lightweight, embedded SQL database. Helps evaluate detection of dependencies in database libraries.

5. zlib – A compression library used in many systems. Useful for assessing discovery of widely embedded libraries in other software.

## Container Images
The ContainerImage folder includes projects built into container images using tools like apt, go install, wget, git clone, and manual copying of files. These images are used to test how well SCA tools handle scanning and analyzing software packaged in container layers.

1. io.livecode.ch – A containerized application built with a mix of shell scripts and third-party tools, useful for checking detection of manually installed and downloaded binaries.

2. pggb – A complex bioinformatics pipeline container built using multiple install mechanisms. Useful to benchmark tools on real-world containerized environments.

3. shapmagn – A scientific container image using custom scripts and copied dependencies. Helps evaluate discovery of files outside of standard package managers.
