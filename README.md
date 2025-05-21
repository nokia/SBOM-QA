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
| 1  | C/C++ code without package manager | C/curl | TBD |
| 2  | C/C++ code without package manager | C/git | TBD |
| 3  | C/C++ code with Conan package manager | C++_CONAN dependencies/CppfrontTemplate | TBD |
| 4  | Go module with dependencies | Go/Go/hugo | TBD |
| 5  | Python module with dependencies | python/fastapi | TBD |
| 6  | npm project with dependencies | Node.js/my-new-folder1/express | TBD |
| 7  | Java project with Maven | java_Maven/java_Maven/elasticsearch | TBD |
| 8  | Container image with apt-install, go install, wget, git clone and local copy of a zip file | ContainerImage/ContainerImage/pggb | TBD |

### 2. Selected SCA tools

| Tool | Nontes |
| ---- | ------ |