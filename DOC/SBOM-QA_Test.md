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

## Observation & Result

## Tools Used
### [Syft](https://github.com/anchore/syft)
**Command:**  
For generating SBOMs for all test targets this command is used:
```
syft -o spdx-json=syft-sbom.json --enrich all --verbose .
```

**Ecosystem:** [Node.js](https://github.com/nokia/SBOM-QA/tree/main/Node.js)

- **Default SBOM:** Generated directly from the project source without performing any compilation step. [syft-default.json](https://github.com/nokia/SBOM-QA/blob/main/Node.js/SBOM/syft-default.json)

- **Compilation Step:**
The project did not originally include a package-lock.json file, which is required to resolve and capture the full dependency tree. To generate it, the following command was executed in test target root:
```
npm install --package-lock
```
**Generated Files:**
- ***package-lock.json*** , ***node_modules***

**Enriched SBOMs:**
  [syft-lock.json](https://github.com/nokia/SBOM-QA/blob/main/Node.js/SBOM/syft-lock.json)


### [Scanoss](https://github.com/scanoss) 
**Command:**  

### [ORT](https://github.com/oss-review-toolkit/ort)  
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
...

**Ecosystem:** 
[C (No package manager)](https://github.com/besser82/libxcrypt)

Given that **ORT** relies on a package manager for SBOM generation, and no package manager was present in this project, no SBOM was produced.

**Ecosystem:** 
[C++ (No package manager)](https://github.com/zeux/meshoptimizer)

In this project, no package manager associated with C++ was identified; However, in the two files listed below, **NPM-related Packages** were detected. 

- ***gltf/package.json*** , ***js/package.json*** 

**Ecosystem:** 
[Node.js](https://github.com/expressjs/express)  

In this project, the following file was identified: 

- ***Package.json***

indicating the use of a package manager: 

- ***NPM*** 

>***Note:*** The **SBOM** was successfully generated without any errors and without the need for any modifications or special configurations.

**Generated SBOM:**
  ...
  
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
  ...



 










### [Trivy](https://github.com/aquasecurity/trivy)  
**Command:** 

---

## Container-Based Tools

### Syft
- Command:  
- Notes / Observations:  

### Tern
- Command:   
- Notes / Observations:  

### Distro2sbom 
- Command:   
- Notes / Observations:

---

## Conclusion

### 1. Ecosystem Point of View
Insights about ecosystem (e.g., package management).

| Aspect              | Observation                                  |
|---------------------|----------------------------------------------|
| Package Management  | Handles dependencies well, but sometimes heavy. |
| Compatibility       | Works across multiple platforms.             |

---

### 2. Tools Point of View
Strengths and weaknesses of tools used.

| Tool       | Strengths                          | Weaknesses                          |
|------------|-----------------------------------|-------------------------------------|
| Tool A     | Easy to use, good docs             | Limited scalability                  |
| Tool B     | Fast performance                   | Poor error messages                  |

---

### 3. Quality Point of View
Validation results and differences

#### 3.1. Validation Results
| File/Module   | Status     | Notes                     |
|---------------|-----------|----------------------------|
| File1.json    | ✅ Passed | All checks OK              |
| File2.json    | ❌ Failed | Missing field `version`    |

#### 3.2. Diffs / Comparisons

| Compared Files        | Differences Found | Notes                       |
|-----------------------|------------------|-----------------------------|
| file1.json vs file2.json | Yes              | Field mismatch on `author`  |
| file3.json vs file4.json | No               | Identical                   |


