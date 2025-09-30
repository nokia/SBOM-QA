# SBOM_Quality-Assurance_Test

## 1. Scope
The scope of this project is to evaluate and benchmark open-source SBOM generation tools in a structured and standardized manner.  

Specifically, the project covers:  
- Open-source software repositories as test targets, spanning multiple programming languages and ecosystems.  
- Generation and analysis of SBOMs in the [SPDX](https://spdx.dev/) format.  
- Use of reference SBOMs exported from original repository dependency graphs to serve as a consistent baseline.  
- Alignment with the [OpenChain Telco SBOM Guide](https://github.com/OpenChain-Project/Specification-Discussion/blob/master/Reference-Material/Telco-SBOM-Guide.md) to ensure standardized practices for SBOM structure, content, and validation.  
- Evaluation of tool performance, accuracy, and coverage to deliver reliable and actionable benchmarking results.  

This project is licensed under the [BSD 3-Clause License](https://github.com/nokia/SBOM-QA/blob/main/LICENSE).  
 

## 2. Terms and Definition
### SBOM
A Software Bill of Materials (SBOM) is a structured inventory of all software components, libraries, and dependencies within an application, including key metadata such as version, license, and origin. It enhances transparency, security, and compliance across the software supply chain.
### SBOM Types
SBOMs can exist at different stages of the software lifecycle, including *Design, Source, Build, Analyzed, Deployed,* and *Runtime*, as defined in the [CISA guidelines](https://www.cisa.gov/sbom).
### Data Format
Data Format refers to the structure in which SBOM information is represented. Common formats include [SPDX](https://spdx.dev/), [CycloneDX](https://cyclonedx.org/), [SWID](https://www.iso.org/standard/65871.html), or other proprietary formats. For the purposes of this case study, the SBOM is represented using the **SPDX** format.
### Package 
A package is a reusable software unit, such as a library or module, distributed via package managers and accompanied by metadata including version, license, and authorship.
### Package Manager 
A package manager is a tool that automates the installation, upgrade, configuration, and removal of software packages, resolving both direct and transitive dependencies; examples include npm, pip, Maven, Gradle, and Conan.
### SCA Tools (Software Composition Analysis)
Tools that analyze software artifacts to identify components and extract metadata (e.g., licenses, versions, suppliers, vulnerabilities), commonly used to generate SBOMs for transparency, compliance, and security.
### Direct Dependency
A direct dependency is a first-level package or component explicitly declared in a project’s configuration or build file.
### Transitive Dependency
A transitive dependency is an indirect package required by a direct dependency of a project.


## 3. Methodology
### 3.1. Tools
**General Tools:**
#### 1. [Syft](https://github.com/anchore/syft) | [Docs](https://anchore.com/opensource/syft/) | [v1.26.1](https://github.com/anchore/syft/releases/tag/v1.26.1)
A CLI tool and Go library for generating an SBOM from container images and filesystems.  
Exceptional for SBOM creation and integrates well with vulnerability scanners like [Grype](https://github.com/anchore/grype).
#### 2. [Trivy](https://github.com/aquasecurity/trivy) | [Docs](https://aquasecurity.github.io/trivy/) | [v0.63.0](https://github.com/aquasecurity/trivy/releases/tag/v0.63.0)
A comprehensive security tool for SBOM generation, vulnerability detection, license analysis, misconfiguration scanning, and secret discovery across container images, filesystems, repositories, VMs, and Kubernetes environments.  
#### 3. [OSS Review Toolkit (ORT)](https://github.com/oss-review-toolkit/ort) | [Docs](https://oss-review-toolkit.org/) | [62.2.0](https://github.com/oss-review-toolkit/ort/releases/tag/62.2.0)
A policy automation and orchestration toolkit for SBOM generation, license compliance, vulnerability detection, and open-source risk management. ORT supports CycloneDX, SPDX, and custom attribution documents, while enabling policy-as-code checks, dependency analysis, and automated reporting across software projects.  
#### 4. [SCANOSS](https://github.com/scanoss/scanoss.py) | [Docs](https://osskb.org/docs) | [v1.26.2](https://github.com/scanoss/scanoss.py/releases/tag/v1.26.2)
The SCANOSS Python package provides a simple library for interacting with SCANOSS APIs and engine, enabling SBOM generation, license compliance, and open-source component identification.  

**Container-based Tools:**
#### 1. [Syft](https://github.com/anchore/syft) | [Docs](https://anchore.com/opensource/syft/) | [v1.30.0](https://github.com/anchore/syft/releases/tag/v1.30.0)
A CLI tool and Go library for generating SBOMs from **container images**.  
It identifies installed packages and their metadata across multiple ecosystems, supporting images from registries, local Docker/OCI images, and tar archives.
#### 2. [Tern](https://github.com/tern-tools/tern) | [Docs](https://tern-tools.github.io/tern/) | [v2.12.1](https://github.com/tern-tools/tern/releases/tag/v2.12.1)
An inspection tool to collect metadata of packages installed in a container image. It analyzes each layer of the image, executes scripts in a chroot environment to gather package information, and generates a detailed report showing packages and their metadata, with optional mapping to Dockerfile instructions.
#### 3. [DISTRO2SBOM](https://github.com/anthonyharrison/distro2SBOM) | [Docs](https://github.com/anthonyharrison/distro2SBOM) | [0.6.0](https://github.com/anthonyharrison/distro2SBOM/releases/tag/v0.6.0)
Generates an SBOM for either an installed application or a complete system installation in formats like SPDX and CycloneDX. It identifies all dependent components of a package and is intended for use in continuous integration systems to maintain accurate SBOM records and support audit requirements.


### 3.2. Tools Selection Criteria 

**Open Source and Actively Maintained:** Only open-source tools with active development communities and regular updates were considered to ensure relevance, reliability, and transparency. 

**Support for SPDX JSON Output:** Since SPDX JSON was the standardized SBOM format chosen for comparison, all selected tools needed to either natively support or allow conversion to this format. 

**Language and Ecosystem Compatibility:** Tools were required to support multiple programming languages and environments, particularly those used in our test targets (e.g., C, C++, Java, Python, Node.js, Go, container images). 

**Alignment with OpenChain Telco SBOM Guide:** Where applicable, tools were evaluated for their ability to generate SBOMs conforming to the recommendations and structure outlined in the OpenChain Telco SBOM Guide. 

**Richness of Metadata:** Tools were assessed on the granularity and completeness of SBOM content, including license information, versioning, source origin, cryptographic hashes, and component relationships. 

## 3.3. Test Target
The test targets linked in this part are the original, publicly available repositories of the respective projects. 

### 1. [C (No package manager)](https://github.com/besser82/libxcrypt)  
[libxcrypt](https://github.com/besser82/libxcrypt) | [tag-v3.9.0](https://github.com/besser82/libxcrypt/releases/tag/v4.4.38) is a modern library for one-way hashing of passwords, supporting various algorithms like bcrypt, md5crypt, and yescrypt. It provides traditional Unix `crypt` interfaces and extended functions for secure password handling. The project does not utilize a package manager, making it suitable for manual integration and analysis.

### 2. [C++ (No package manager)](https://github.com/zeux/meshoptimizer)  
[MeshOptimizer](https://github.com/zeux/meshoptimizer) | [tag-v0.24](https://github.com/zeux/meshoptimizer/releases/tag/v0.24) is an open-source C++ library developed by Arseny Kapoulkine, providing algorithms to optimize meshes for modern GPU vertex and index processing pipelines. It can reindex an existing index buffer or generate an entirely new set of indices from an unindexed vertex buffer. The project does not utilize a package manager, making it suitable for manual integration and analysis.

### 3. [C++ (Conan)](https://github.com/catchorg/Catch2)  
[Catch2](https://github.com/catchorg/Catch2) | [tag-v3.9.0](https://github.com/catchorg/Catch2/releases/tag/v3.9.0) is a modern, header-only testing framework for C++. It provides robust unit testing, micro-benchmarking, and test case management. For this study, the project is managed using the [Conan](https://conan.io/) package manager.

### 4. [Go](https://github.com/gohugoio/hugo)  
[Hugo](https://github.com/gohugoio/hugo) | [tag-v0.147.4](https://github.com/gohugoio/hugo/releases/tag/v0.147.4) is a fast and flexible static site generator written in Go. It is widely used for websites, blogs, documentation, and portfolios.

### 5. [Node.js](https://github.com/expressjs/express)  
[Express](https://github.com/expressjs/express) | [tag-v5.1.0](https://github.com/expressjs/express/releases/tag/v5.1.0) is a minimal and flexible Node.js web application framework that provides robust features for building web and mobile applications.

### 6. [Python (FastAPI)](https://github.com/fastapi/fastapi) | [Python (GPT Engineer)](https://github.com/AntonOsika/gpt-engineer)
- [FastAPI](https://github.com/fastapi/fastapi) | [tag-0.116.0](https://github.com/fastapi/fastapi/releases/tag/0.116.0) is a modern, fast (high-performance) web framework for building APIs with Python 3.7+ based on standard Python type hints. It is widely used for developing web applications and APIs efficiently.

- [GPT Engineer](https://github.com/AntonOsika/gpt-engineer) | [tag-v0.3.1](https://github.com/AntonOsika/gpt-engineer/releases/tag/v0.3.1) is a Python project designed to facilitate building AI-driven solutions and applications, providing a structured environment for rapid prototyping and experimentation.

### 7. [Java (Maven-managed)](https://github.com/bytedeco/javacv)  
[JavaCV](https://github.com/bytedeco/javacv) | [tag-1.5.12](https://github.com/bytedeco/javacv/releases/tag/1.5.12) is a Java interface to OpenCV, FFmpeg, and other computer vision and machine learning libraries. It provides a comprehensive set of tools for image and video processing, machine learning, and computer vision tasks. The project is managed using the [Maven](https://maven.apache.org/) package manager.

### 8. [ContainerImage](https://github.com/pangenome/pggb)  
[pggb](https://github.com/pangenome/pggb) | [tag-v0.7.4](https://github.com/pangenome/pggb/releases/tag/v0.7.4) builds pangenome variation graphs from input sequences using wfmash, seqwish, smoothxg, gfaffix, and odgi.  

>***Note:*** The project provides a **Dockerfile** for containerized usage, enabling local builds or pulls from the GitHub Container Registry.

## 3.4. Test Targets Selection Criteria 
**Real-World Relevance:** Only publicly available, widely used open-source projects were considered to ensure practical evaluation of SCA tools.

**Ecosystem Diversity:** Projects cover multiple languages, build systems, and with or without package managers.

**Reference SBOM Availability:** For each test target, a Reference SBOM was available.

## 3.5. Reference SBOM
A **Reference SBOM** is a standardized, machine-readable inventory of a project's dependencies and associated metadata, such as versions, licenses, and transitive relationships. It is generated directly from the **dependency graph** of the original, publicly available repositories of the respective test targets.

These SBOMs provide a canonical view of all software components, including direct and transitive dependencies, and serve as a baseline for comparison and validation. The dependency graph is a summary of the manifest and lock files stored in a repository and any dependencies that are submitted for the repository using the dependency submission API ([GitHub Docs: Dependency Graph](https://docs.github.com/en/code-security/supply-chain-security/understanding-your-software-supply-chain/about-the-dependency-graph?utm_source=chatgpt.com)).

For each test target, the Reference SBOM was exported from its **GitHub repository** using automated SBOM generation tools. These SBOMs capture the original dependency tree and associated metadata (e.g., versions, licenses) before any modifications or local testing. GitHub facilitates this process by allowing users to export an SBOM from a repository's dependency graph via the UI or REST API, producing an SPDX-compatible JSON file ([GitHub Docs: Exporting SBOM](https://docs.github.com/en/code-security/supply-chain-security/understanding-your-software-supply-chain/exporting-a-software-bill-of-materials-for-your-repository?utm_source=chatgpt.com)).

## 3.6. Comparison and Analysis 
The generated SBOMs from each tool were benchmarked against the corresponding reference SBOMs. 
The comparison focused on: 
Dependency coverage (direct and transitive) 
Accuracy of versioning 
Presence of critical metadata (license, hash, source URL) 

## 3.7. Validation 
[OpenChain Telco SBOM Validator](https://pypi.org/project/openchain-telco-sbom-validator/0.3.0/) was used to validate the structural compliance and metadata quality of each generated SBOM. 
Validation criteria included: 
Conformance to SPDX specification 
Inclusion of mandatory and recommended fields 
Logical consistency (e.g., relationships, identifiers) 

---

## 4. Observation & Result

### Tools Used
#### 1. [Syft](https://github.com/anchore/syft)
**Command:**  
For generating SBOMs for all test targets this command is used:
```
syft -o spdx-json=syft-sbom.json --enrich all --verbose .
```

**Ecosystem:** 
[Node.js](https://github.com/nokia/SBOM-QA/tree/main/Node.js)

- **Default SBOM:**
[syft-default.json](https://github.com/nokia/SBOM-QA/blob/main/Node.js/SBOM/syft-default.json)

Generated directly from the project source without performing any compilation step. 

- **Compilation Step:**

The project did not originally include a package-lock.json file, which is required to resolve and capture the full dependency tree. To generate it, the following command was executed in test target root:
```
npm install --package-lock
```
**Generated Files:**
- ***package-lock.json*** , ***node_modules***

**Enriched SBOMs:**
[syft-lock.json](https://github.com/nokia/SBOM-QA/blob/main/Node.js/SBOM/syft-lock.json)

**Ecosystem:** 
[Go](https://github.com/gohugoio/hugo)

- **Default SBOM:**

**Ecosystem:**
[Python (FastAPI)](https://github.com/fastapi/fastapi)

- **Default SBOM:** 

- **Compilation Step:**

The project did not include a pdm.lock file. To generate it and pin all dependencies, the following command was executed:

```
pdm lock
```
Dependencies must be installed for the environment using:

```
pdm install
```

**Enriched SBOMs:**
...

**Ecosystem:** 
[Python (GPT Engineer)](https://github.com/AntonOsika/gpt-engineer)

- **Default SBOM:**

- **Compilation Step:**

The project included both pyproject.toml and poetry.lock. To install only the production dependencies (excluding development packages), the following command was executed: 

```
poetry install --no-dev
```

**Enriched SBOMs:**
...

**Ecosystem:** 
[C++ (Conan)](https://github.com/catchorg/Catch2)


- **Default SBOM:** 

**Ecosystem:** 
[C (No package manager)](https://github.com/besser82/libxcrypt)

- **Default SBOM:** 

**Ecosystem:** 
[C++ (No package manager)](https://github.com/zeux/meshoptimizer)

- **Default SBOM:** 

**Ecosystem:**
[Java (Maven-managed)](https://github.com/bytedeco/javacv) 

- **Default SBOM:**

- **Compilation Step:** Build

The project was compiled to ensure that all direct and transitive dependencies were resolved and    packaged into build artifacts (target/*.jar). following command was executed in tese target root: 

```
mvn clean package -DskipTests
```

**Generated Files:**
- ***target/*.jar***

**Result:**

Ensures a richer and more accurate SBOM including both direct and transitive dependencies.

**Enriched SBOMs:**
...












#### 2. [Scanoss](https://github.com/scanoss) 
**Command:**  

#### 3. [ORT](https://github.com/oss-review-toolkit/ort)  
**Command:**

For generating SBOMs for all test targets this command is used:

**Analyze phase:**
```
ort analyze -i /path/to/your/project -o /path/to/output-dir 
```

**Report phase:**
```
ort report -i /path/to/analyzer-result.yml -o /path/to/output-dir -f spdxDocument 
```

>***Note:*** The resulting output is an SBOM compliant with SPDX version 2.2, delivered as a YAML file. Although the maintainers of ORT suggested the use of the following parameter to enforce SPDX version 2.3, no version change was observed in practice: 
```
-O SpdxDocument=spdx_version=SPDX-2.3 
```

The generation of an **SBOM** with the **ORT** is structured into several phases: 

•	**Analyzer** 

•	**Scanner**

•	**Advisor** 

•	**Evaluator** 

•	**Reporter**

These phases can either be executed sequentially or selectively, depending on the requirements. The **Analyzer Phase** is ***mandatory***, as its output serves as the essential input for all subsequent stages and therefore cannot be omitted. 

In the examined workflow, only the Analyzer and Reporter phases were executed. 
The Analyzer phase produces the file ***analyzer-result.yml*** 
Then the Reporter phase use this file as input file.

**Ecosystem:** 
[Go](https://github.com/gohugoio/hugo)

In this project, the following files were identified: 

- ***docs/go.mod*** , ***go.mod*** , ***docs/package.json*** , ***internal/warpc/js/package.json*** 

Indicating the use of two different **Package Managers**: 

- **GoMod & NPM** 

>***Note:*** The **SBOM** was successfully generated without any errors and without the need for any modifications or special configurations. 

**Generated SBOM:**
[ORT-GO.json](https://github.com/nokia/SBOM-QA/blob/main/Go/SBOM/ort.json)

**Ecosystem:** 
[C (No package manager)](https://github.com/besser82/libxcrypt)

Given that ORT relies on a package manager for SBOM generation, and no package manager was present in this project, the generated SBOM only included the project name as a package.

**Generated SBOM:**
[ORT-C-NP.json](https://github.com/nokia/SBOM-QA/blob/main/C-NP/SBOM/ort%20.json)

**Ecosystem:** 
[C++ (No package manager)](https://github.com/zeux/meshoptimizer)

In this project, no package manager associated with C++ was identified; However, in the two files listed below, **NPM-related Packages** were detected. 

- ***gltf/package.json*** , ***js/package.json***

**Generated SBOM:**
[ORT-C++-NP.json](https://github.com/nokia/SBOM-QA/blob/main/C%2B%2B-NP/SBOM/ortC%2B%2BMeShop.json)


**Ecosystem:** 
[Node.js](https://github.com/expressjs/express)  

In this project, the following file was identified: 

- ***Package.json***

indicating the use of a package manager: 

- ***NPM*** 

>***Note:*** The **SBOM** was successfully generated without any errors and without the need for any modifications or special configurations.

**Generated SBOM:**
[ORT-Node-js.json](https://github.com/nokia/SBOM-QA/blob/main/Node.js/SBOM/node.js.ORT.ScanSbom.json)


**Ecosystem:**
[Java (Maven-managed)](https://github.com/bytedeco/javacv) 

During the process, an error related to the Maven compiler was encountered, which necessitated modifications in the ***pom.xml*** file as described below: 

        <artifactId>maven-compiler-plugin</artifactId> 

        <version>3.12.1</version> 

        <configuration> 

          <source>1.8</source> 

          <target>1.8</target> 

In addition, the following three files were identified: 

- ***platform/pom.xml*** ,  ***pom.xml*** , ***samples/pom.xml***

Indicating that the project relied on a single package manager: 

- ***Maven*** 

After the version was corrected, **ORT** was ultimately able to generate the **SBOM** successfully without errors.

**Generated SBOM:**
[ORT-Java-Maven.json](https://github.com/nokia/SBOM-QA/blob/main/Java_Maven/SBOM/normal.ort.json)

**Ecosystem:** 
[C++ (Conan)](https://github.com/catchorg/Catch2)

In this section, several points should be highlighted.  

- First, since ORT encountered errors with Conan versions 2.x, it was necessary to downgrade Conan to version 1.66.0.  

- Second, because a Linux-based operating system was used, one of the viable approaches for installing Conan involved the creation of a conan-venv, which was adopted in this case.  

It should also be noted that the project included Bazel; therefore, ***Bazel(version:8.3.1)*** and ***Buildizer(version:1.5.0)*** were installed, as **ORT** would otherwise have failed with errors.  

- Finally, the following files were identified: 

- ***MODULE.bazel*** , ***.conan/test_package/conanfile.py*** , ***Conanfile.py*** 

and in total, two package managers were detected: 

- ***Bazel & Conan***

**Generated SBOM:**
[ORT-C++-CONAN.json](https://github.com/nokia/SBOM-QA/blob/main/C%2B%2B_CONAN/SBOM/ort.json)

**Ecosystem:**
[Python (FastAPI)](https://github.com/fastapi/fastapi)

Since the project utilized the PDM package manager, which was not included in the list of package managers supported by ORT, no SBOM was generated as a result. 


**Ecosystem:**
[Python (GPT Engineer)](https://github.com/AntonOsika/gpt-engineer)

In this project, the following two files were identified: 

- ***projects/example-improve/requirements.txt*** , ***poetry.lock*** 

 Ultimately two package managers were utilized: 

- ***PIP & Poetry*** 

The SBOM was successfully generated without any errors. 

**Generated SBOM:**
[ORT-python.json](https://github.com/nokia/SBOM-QA/blob/main/Python2/SBOM/ort.json)

 
#### 4. [Trivy](https://github.com/aquasecurity/trivy)  
**Command:** (In test target root):

```
trivy fs --format spdx-json --scanners vuln,license,secret,misconfig --output trivy-sbom.spdx.json .
```

**Ecosystem:** 
[Node.js](https://github.com/expressjs/express)  

**Generated SBOM:**
...

- **Compilation Step:**

The project did not originally include a package-lock.json file, which is required to resolve and capture the full dependency tree without actually installing dependencies, the following command was executed in test target root: 

```
npm install --package-lock-only 
```

**Created Files:**

- ***package-lock.json***

To create a clean environment with only production dependencies installed (excluding devDependencies), the following command was executed: 

```
npm ci --only=production
```
**Enriched SBOMs:**
...

**Ecosystem:** 
[C++ (Conan)](https://github.com/catchorg/Catch2)

**Generated SBOM:**
...

**Ecosystem:** 
[Go](https://github.com/gohugoio/hugo)

**Generated SBOM:**
...

- **Compilation Step:**

To ensure all required dependencies are included and the module files are consistent, the following command was executed in the project root: 

```
go mod tidy
```

**Updated Files:**

- ***go.mod*** , ***go.sum***

**Enriched SBOMs:**
...

**Ecosystem:** 
[C++ (No package manager)](https://github.com/zeux/meshoptimizer)

**Generated SBOM:**
...

**Ecosystem:**
[Python (FastAPI)](https://github.com/fastapi/fastapi)

**Generated SBOM:**
...

- **Compilation Step:**

The project did not include a pdm.lock file. To generate it and pin all dependencies, the following command was executed:

```
pdm lock
```

Dependencies must be installed for the environment using:

```
pdm install
```

**Enriched SBOMs:**
...

> **Note:** As of now, Trivy does not support scanning Python projects managed with PDM. Specifically, Trivy does not parse the pdm.lock file, which means it cannot fully resolve and capture the project's dependency tree. This limitation affects the accuracy and completeness of Software Bill of Materials (SBOM) generation for PDM-managed Python projects. 

For more information and to track the progress of this feature, refer to the following GitHub issue: 
[Trivy GitHub Issue: Add support for PDM lockfile parsing](https://github.com/aquasecurity/trivy/issues/9410?utm_source=chatgpt.com)

**Ecosystem:**
[Python (GPT Engineer)](https://github.com/AntonOsika/gpt-engineer)

**Generated SBOM:**
...

**Ecosystem:** 
[C (No package manager)](https://github.com/besser82/libxcrypt)

**Generated SBOM:**
...

**Ecosystem:**
[Java (Maven-managed)](https://github.com/bytedeco/javacv) 

**Generated SBOM:**
...









---

## Container-Based Tools  

In the selected project, the container image was based on a Linux distribution. Therefore, in order to properly execute the image and generate its corresponding SBOM, all tasks were carried out within a Linux operating system environment. 

### 1. Distro2sbom 

**Observations:** 

In order to generate an SBOM  using distro2sbom, direct access to the root filesystem is required. Since running the tool against the live system root may not always be feasible or safe, the system root was first exported into a separate directory. This exported filesystem served as an isolated input for the SBOM generation process. 

By performing the export step, distro2sbom was able to analyze the complete set of installed packages and system files, ensuring that the resulting SBOM accurately represents the environment. After the export was completed, the tool was executed against the target directory, successfully producing the SBOM.

**Command:**

- ***Extract image:***
```
docker create --name tmp <image name> 
```
- ***Export container filesystem:***
```
docker export tmp -o <fileName.tar> 
``` 
- ***Extract the tar file into root filesystem:***
```
tar -C <directoryName>  -xf <fileName.tar> 
``` 
- ***Remove the temporary container:***
```
docker rm tmp 
``` 
- ***For Generating SBOM:***
```
distro2sbom --root <path-to-rootFileSystem> -s --sbom <spdx|cyclonedx> --format <json|xml|yaml> -o <path-to-output-file>  
```
**Generated SBOM:**

> **Note:**
Since a Linux environment was used, a dedicated Python virtual environment was created to ensure isolation and reproducibility. In this environment, the distro2sbom tool was installed as the main tool for generating SBOM. 


### 2. Tern
There are three main approaches to generating an SBOM with Tern: 

**1.	Analyzing an exported root filesystem:** 
In this method, the system’s root filesystem is exported into a dedicated directory.   
Tern is then executed against that directory to analyze all installed packages and generate the SBOM.  
**Commands:**
```
docker export $(docker create <image name>) | tar -C  </path/to/directory> -xvf –  
```

```
tern report -l </path/to/directory>  -f spdxjson -o <path/to/output/name.spdx.json>   
```
**2.⁠ ⁠Parsing a Dockerfile:**
Tern can process a Dockerfile directly to infer the layers and dependencies defined in the build instructions.
**Commands:**
```
tern report -d Dockerfile -o <path/to/output/name.spdx.json> -f json   
```
**3.⁠ ⁠Directly analyzing a container image: (not used in this project)**
Tern can be pointed to a container image (local or remote) to generate an SBOM without needing the Dockerfile or exported filesystem. 

**Commands:**
```
tern report -i <image:tag> > sbom_image.json   
```

> **Note:**
> In this project, the first two approaches were applied: 
> - Exporting and analyzing the root filesystem. 
> - Generating reports from the Dockerfile.
>    
> The third approach (directly analyzing the image) is also supported by Tern, but it was not used in this case. 

### 3. Syft
- Command:   
- Notes / Observations:

---

## 5. Conclusion

### 5.1. Ecosystem Point of View
Insights about ecosystem (e.g., package management).

| Aspect              | Observation                                                                 |
|---------------------|-----------------------------------------------------------------------------|
| Package Management  | Ecosystems with package managers (npm, Maven, Poetry) produced richer SBOMs. |
| Compatibility       | C/C++ projects without package managers had weak coverage.                  |
| Accuracy            | Lockfiles (npm, poetry.lock) improved accuracy of transitive dependencies.  |
| Completeness        | Java builds included additional artifacts (JARs), enriching SBOMs.          |

---

### 5.2. Tools Point of View
Strengths and weaknesses of tools used.

| Tool     | Strengths                                                                 | Weaknesses                                  |
|----------|---------------------------------------------------------------------------|---------------------------------------------|
| Syft     | Easy to use, fast, supports many ecosystems, SPDX JSON output             | Limited accuracy without lock/build files    |
| Trivy    | Rich scanning (vulns, misconfigs, licenses, secrets), SBOM support        | Weak PDM (Python) support, some ecosystems partial |
| ORT      | Comprehensive analysis, policy as code, SPDX compliant                    | Heavy setup, requires package managers, slower |
| Scanoss  | Strong license compliance checks, lightweight                             | Limited ecosystem coverage, weaker metadata  |


---

### 5.3. Quality Point of View
Validation results and differences

#### 5.3.1. Validation Results

##### 1. [Syft](https://github.com/anchore/syft)

| Ecosystem   | Compliant | Error Types                        | Notes                                    |
|-------------|-----------|------------------------------------|------------------------------------------|
| Go          | ❌ Failed | Missing version, Missing supplier  | 10 validation errors in tidy-vendor.json |
| Python      | ✅ Passed | -                                  | All checks OK                            |
| Node.js     |         | -                                  | SBOM valid                               |
| Java        |         | Missing license info               | Needs enrichment from build artifacts    |
| C           |      | Missing version                    | Package without version metadata         |
| C++ (Conan) |      | -                                  | All mandatory SPDX fields included       |
| C++  |                |                                     |           |          |          |            |           |
| Python2  |                |                                     |           |          |          |            |           |

##### 2. [Trivy](https://github.com/aquasecurity/trivy)

| Ecosystem   | Compliant | Error Types                        | Notes                                    |
|-------------|-----------|------------------------------------|------------------------------------------|
| Go          |     | Missing version, Missing supplier  | 10 validation errors in tidy-vendor.json |
| Python      |     | -                                  | All checks OK                            |
| Node.js     |         | -                                  | SBOM valid                               |
| Java        |      | Missing license info               | Needs enrichment from build artifacts    |
| C           |       | Missing version                    | Package without version metadata         |
| C++ (Conan) |       | -                                  | All mandatory SPDX fields included       |
| C++  |                |                                     |           |          |          |            |           |
| Python2  |                |                                     |           |          |          |            |           |

##### 3. [ORT](https://github.com/oss-review-toolkit/ort)

| Ecosystem   | Compliant | Error Types                        | Notes                                    |
|-------------|-----------|------------------------------------|------------------------------------------|
| Go          | ❌ Failed | Missing version, Missing supplier  | 10 validation errors in tidy-vendor.json |
| Python      | ✅ Passed | -                                  | All checks OK                            |
| Node.js     |       | -                                  | SBOM valid                               |
| Java        |     | Missing license info               | Needs enrichment from build artifacts    |
| C           |     | Missing version                    | Package without version metadata         |
| C++ (Conan) |     | -                                  | All mandatory SPDX fields included       |
| C++  |                |                                     |           |          |          |            |           |
| Python2  |                |                                     |           |          |          |            |           |

##### 4. [SCANOSS](https://github.com/scanoss/scanoss.py)

| Ecosystem   | Compliant | Error Types                        | Notes                                    |
|-------------|-----------|------------------------------------|------------------------------------------|
| Go          |     | Missing version, Missing supplier  | 10 validation errors in tidy-vendor.json |
| Python      |     | -                                  | All checks OK                            |
| Node.js     |     | -                                  | SBOM valid                               |
| Java        |      | Missing license info               | Needs enrichment from build artifacts    |
| C           |     | Missing version                    | Package without version metadata         |
| C++ (Conan) |      | -                                  | All mandatory SPDX fields included       |
| C++  |                |                                     |           |          |          |            |           |
| Python2  |                |                                     |           |          |          |            |           |

#### 5.3.2. Diffs / Comparisons  

##### 1. [Syft](https://github.com/anchore/syft)

| Ecosystem   | Compared Files                   | Differences Found | Version Changes | New Packages | Removed Packages | License Changes  | Notes                          |
|-------------|----------------------------------|------------------|----------------|--------------|------------------|-----------------|--------------------------------|
| C           | ref.json vs  |             |     |       |               |           |        |
| C++ (Conan) | ref.json vs              |             |      |           |              |      |         |
| Python      | ref.json vs            |             |        |        |             |            |                   |
| Node.js     | ref.json vs       |             |     |         |             |            |          |
| Java        | ref.json vs             |            |      |       |         |          |         |
| Go          | ref.json vs             |            |           |         |           |             |                |
| C++         | ref.json vs                |                                     |           |          |          |            |           |
| Python2     | ref.json vs                |                                     |           |          |          |            |           |

##### 2. [Trivy](https://github.com/aquasecurity/trivy)

| Ecosystem   | Compared Files                   | Differences Found | Version Changes | New Packages | Removed Packages | License Changes  | Notes                          |
|-------------|----------------------------------|------------------|----------------|--------------|------------------|-----------------|--------------------------------|
| C           | ref.json vs   |             |     |       |               |           |        |
| C++ (Conan) | ref.json vs              |             |      |           |              |      |         |
| Python      | ref.json vs            |             |        |        |             |            |                   |
| Node.js     | ref.json vs        |             |     |         |             |            |          |
| Java        | ref.json vs             |            |      |       |         |          |         |
| Go          | ref.json vs            |            |           |         |           |             |                |
| C++         | ref.json vs              |                                     |           |          |          |            |           |
| Python2     | ref.json vs               |                                     |           |          |          |            |           |

##### 3. [ORT](https://github.com/oss-review-toolkit/ort)

| Ecosystem   | Compared Files                   | Differences Found | Version Changes | New Packages | Removed Packages | License Changes  | Notes                          |
|-------------|----------------------------------|------------------|----------------|--------------|------------------|-----------------|--------------------------------|
| C           | ref.json vs   |             |     |       |               |           |        |
| C++ (Conan) | ref.json vs             |             |      |           |              |      |         |
| Python      | ref.json vs           |             |        |        |             |            |                   |
| Node.js     | ref.json vs        |             |     |         |             |            |          |
| Java        | ref.json vs            |            |      |       |         |          |         |
| Go          | ref.json             |            |           |         |           |             |                |
| C++         | ref.json vs        |                                     |           |          |          |            |           |
| Python2     | ref.json vs           |                                     |           |          |          |            |           |

##### 4. [SCANOSS](https://github.com/scanoss/scanoss.py)

| Ecosystem   | Compared Files                   | Differences Found | Version Changes | New Packages | Removed Packages | License Changes  | Notes                          |
|-------------|----------------------------------|------------------|----------------|--------------|------------------|-----------------|--------------------------------|
| C           | ref.json vs   |             |     |       |               |           |        |
| C++ (Conan) | ref.json vs            |             |      |           |              |      |         |
| Python      | ref.json vs           |             |        |        |             |            |                   |
| Node.js     | ref.json vs       |             |     |         |             |            |          |
| Java        | ref.json vs             |            |      |       |         |          |         |
| Go          | ref.json vs          |            |           |         |           |             |                |
| C++         | ref.json vs             |                                     |           |          |          |            |           |
| Python2     | ref.json vs             |                                     |           |          |          |            |           |
