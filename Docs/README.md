
# MedVision
**All-in-One Medical Imaging & PACS Platform**

MedVision is a modular medical imaging system built from the ground up to study
DICOM internals, medical image processing, and PACS communication using C++ on Windows.

This project focuses on understanding how medical imaging systems work internally
rather than building a clinical-grade product.

## ?? Project Status

### Completed Components
- ? **MedVision.Dicom** - DICOM I/O library (100%)
- ? **MedVision.Dicom.Tests** - Unit tests (100%)
- ? **Documentation Package** - Complete architecture & guides (100%)

### In Progress
- ?? **MedVision.Viewer** - DICOM viewer application (0% - Planning Complete)

## ?? Quick Start

### For New Developers
**START HERE:** Read [`Getting_Started.md`](Getting_Started.md)

This comprehensive guide contains:
- What's been built
- What's next
- Complete action plan
- Step-by-step instructions

### Documentation Index
| Document | Purpose | When to Read |
|----------|---------|--------------|
| **[Getting_Started.md](Getting_Started.md)** | ? Start here - Complete onboarding | First time |
| **[MedVision_Viewer_Architecture.md](MedVision_Viewer_Architecture.md)** | System design & 10-week roadmap | Before coding |
| **[Phase1_Implementation.md](Phase1_Implementation.md)** | Week 1-2 detailed guide | During development |
| **[Project_Setup_Checklist.md](Project_Setup_Checklist.md)** | VS project creation steps | Setup day |
| **[Feature_Roadmap.md](Feature_Roadmap.md)** | 150+ features vs MicroDicom | Planning |
| **[Quick_Reference.md](Quick_Reference.md)** | Daily development reference | Daily |
| **[Solution_Structure.md](Solution_Structure.md)** | Project layout | Reference |
| **[CHANGELOG.md](CHANGELOG.md)** | Track all changes | Ongoing |

## ?? Key Objectives
- ? Implement DICOM reader/writer (COMPLETE)
- ?? Build a medical image rendering pipeline (IN PROGRESS - Phase 1)
- ? Build desktop DICOM viewer (PLANNED - Phase 1-4)
- ? Support basic PACS communication (PLANNED - Phase 5)
- ? Explore 2D and 3D medical imaging (PLANNED - Phase 4)
- ? Design scalable desktop architecture (COMPLETE)

## ??? Technology Stack

### Core Technologies (Finalized)
- **Language:** C++14
- **UI:** Win32 + ImGui
- **Rendering:** DirectX 11
- **Database:** SQLite
- **Build:** Visual Studio 2022
- **CI/CD:** GitHub Actions

### Libraries
- **MedVision.Dicom** ? - DICOM I/O (zero dependencies)
- **MedVision.Imaging** ? - Image processing (to be built)
- **MedVision.Rendering** ? - GPU rendering (to be built)
- **MedVision.Database** ? - Local database (Phase 3)
- **MedVision.Pacs** ? - Network (Phase 5)

## ?? Current Progress

| Phase | Duration | Features | Status | Progress |
|-------|----------|----------|--------|----------|
| **Planning** | - | Documentation | ? Complete | 100% |
| **Phase 1** | 2 weeks | Foundation | ?? Not Started | 0% |
| **Phase 2** | 2 weeks | Core Features | ? Planned | 0% |
| **Phase 3** | 2 weeks | Advanced | ? Planned | 0% |
| **Phase 4** | 2 weeks | 3D/MPR | ? Planned | 0% |
| **Phase 5** | 2 weeks | PACS | ? Planned | 0% |

**Overall:** 4% complete (MedVision.Dicom library)  
**Next Milestone:** Phase 1 Week 1 (MedVision.Imaging)

## ?? MedVision.Viewer Features

Building a viewer similar to **[MicroDicom](https://www.microdicom.com/)**

### Target Features (116 features across 5 phases)
- ? Core viewing (single image, W/L, pan, zoom)
- ? Series navigation & thumbnails
- ? Measurements & annotations
- ? Multi-planar reconstruction (MPR)
- ? 3D volume rendering
- ? PACS Query/Retrieve
- ? Export & print
- ? Local database

See [`Feature_Roadmap.md`](Feature_Roadmap.md) for complete feature list.

## ?? Documentation Package

**9 comprehensive documents** covering every aspect:

1. **Getting_Started.md** ? - Start here
2. **MedVision_Viewer_Architecture.md** - Complete design
3. **Phase1_Implementation.md** - Week 1-2 guide
4. **Project_Setup_Checklist.md** - Setup steps
5. **Feature_Roadmap.md** - Feature tracking
6. **Quick_Reference.md** - Daily reference
7. **Solution_Structure.md** - Project layout
8. **CHANGELOG.md** - Change tracking
9. **DOCUMENTATION_PACKAGE_SUMMARY.md** - This package overview

**Total:** ~30 pages of documentation, 15+ code templates

## ?? Getting Started

### Prerequisites
- Visual Studio 2022
- Windows SDK 10.0+
- Git

### Build Existing Code
```powershell
# Clone repository
git clone https://github.com/gaukem/MedVision.git
cd MedVision

# Build MedVision.Dicom
msbuild MedVision.Dicom/MedVision.Dicom.vcxproj /p:Configuration=Debug /p:Platform=x64

# Run tests
msbuild MedVision.Dicom.Tests/MedVision.Dicom.Tests.vcxproj /p:Configuration=Debug /p:Platform=x64
vstest.console.exe bin\x64\Debug\MedVision.Dicom.Tests.dll
```

### Start Building the Viewer
1. Read [`Getting_Started.md`](Getting_Started.md)
2. Follow [`Project_Setup_Checklist.md`](Project_Setup_Checklist.md)
3. Begin [`Phase1_Implementation.md`](Phase1_Implementation.md)

## ?? Learning Resources

### DICOM
- [DICOM Standard](https://www.dicomstandard.org/)
- [Sample DICOM Files](https://www.dicomlibrary.com/)

### DirectX 11
- [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/direct3d11/)
- [HLSL Reference](https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/)

### Medical Imaging
- [MicroDicom](https://www.microdicom.com/) - Reference viewer
- [3D Slicer](https://www.slicer.org/) - Advanced features
- [Horos](https://horosproject.org/) - Open source viewer

## ?? Contributing

This is an educational project focused on learning medical imaging systems.

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

See development workflow in [`Quick_Reference.md`](Quick_Reference.md)

## ?? Support

- **Documentation:** Check `Docs/` folder first
- **GitHub Issues:** https://github.com/gaukem/MedVision/issues
- **Quick Help:** [`Quick_Reference.md`](Quick_Reference.md)

## ?? Disclaimer

This software is for **educational and research purposes only**.  
**NOT FOR CLINICAL USE.**  
Not intended for medical diagnosis or treatment.
