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
| 1  | C++ code without package manager | [C++/electron](C++/electron) | TBD |
| 2  | C code without package manager | [C/curl](C/curl) | TBD |
| 3  | C++ code with Conan package manager | [C++_CONAN/Coronan](C++_CONAN/Coronan) | TBD |
| 4  | Go module with dependencies | [Go/hugo](Go/hugo) | TBD |
| 5  | Python module with dependencies | [python/fastapi](python/fastapi) | TBD |
| 6  | npm project with dependencies | [Node.js/express](Node.js/express) | TBD |
| 7  | Java project with Maven | [java_Maven/elasticsearch](java_Maven/elasticsearch) | TBD |
| 8  | Container image with apt-install, go install, wget, git clone and local copy of a zip file | [ContainerImage/pggb](ContainerImage/pggb) | TBD |

### 2. Selected SCA tools

| Tool | Nontes |
| ---- | ------ |


# Folder Descriptions

Descriptions of each test folder and what it contains.

## C++ Projects
This folder contains C++ projects that are built without using a package manager. They typically use custom build systems or plain CMake.

**1. electron** – An open-source game engine for Windows and Linux. Not to be confused with GitHub's Electron framework, this project provides a complex, full-scale C++ codebase for a game engine with manual dependency handling.

## C++ with Conan Package Manager
The C++_CONAN folder includes C++ projects that explicitly use the Conan package manager to manage dependencies.

**1. Coronan** – A simple CMake-based C++ project that uses Conan to fetch and integrate common libraries like zlib or gtest. It serves as an example for integrating Conan with modern C++ projects.

## C Projects (No Package Manager)
The C folder contains well-known open-source C projects, built and configured manually without dependency managers like vcpkg or Conan.

**1. curl** – A powerful command-line tool and library (libcurl) for transferring data using various protocols including HTTP, FTP, and SMTP. It's known for its portable C codebase and rich feature set.

## Container Images
The ContainerImage folder contains folders or Dockerfiles used to build container images. These images may install software using a combination of package managers, custom binaries, and manual setups.

**1. pggb** – A bioinformatics pipeline for constructing pangenome graphs. It integrates several tools like seqwish, smoothxg, and others. The software is distributed as a container for easier reproducibility and execution in bioinformatics workflows.

## Go Projects
The Go folder contains projects written in the Go programming language, typically using Go modules for dependency management.

**1. hugo** – A fast, modern static site generator written in Go. It converts markdown files into complete HTML websites and is widely used in the developer and open-source communities.

## Node.js 
folder includes projects built using the Node.js runtime, often managed with npm or yarn.

**1. express** - A minimal and flexible web application framework for Node.js. It provides a thin layer of fundamental web features and is widely used to create server-side applications and REST APIs.

## Java Maven Projects
The java_Maven folder contains Java projects that use the Maven build system for compilation and dependency resolution.

**1. elasticsearch** - A distributed, scalable, real-time search and analytics engine built in Java. It's used to index and query large volumes of data and serves as the core engine behind the Elastic Stack.

## Python Projects
The Python folder contains software projects written in Python, using tools like pip or poetry for environment and dependency management.

**1. fastapi** - A modern Python web framework designed for building APIs quickly with automatic OpenAPI and JSON Schema generation. It’s built on top of Starlette and Pydantic and supports asynchronous programming.


