# MedVision.Viewer - Changelog

All notable changes to the MedVision.Viewer project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Phase 1 Week 1 - 2024-02-11 (Update 2)

#### Added - Project Organization
- **MedVision.Imaging.vcxproj.filters** - Visual Studio filter file for proper file organization
  - Header Files filter with nested medvision/imaging structure
  - Source Files filter
  - Proper organization in Solution Explorer

#### Added - DICOM Tags (MedVision.Dicom)
- **StudyDescription** (0008,1030) - Study description tag
- **WindowCenter** (0028,1050) - Default window center for display
- **WindowWidth** (0028,1051) - Default window width for display
- **RescaleIntercept** (0028,1052) - Rescale intercept for Hounsfield units
- **RescaleSlope** (0028,1053) - Rescale slope for Hounsfield units

**Rationale:** These tags are required by MedVision.Imaging for proper image display and processing. Window/Level and Rescale parameters are essential for medical image viewing.

### Phase 1 Week 1 - 2024-02-11

#### Added - MedVision.Imaging Library
- **MedVision.Imaging project** - Image processing library created
  - DicomImage class - DICOM image wrapper with patient/study info access
  - PixelDataProcessor class - Pixel data extraction (8-bit, 16-bit signed/unsigned)
  - WindowLevel class - Window/Level transformations with CT presets
  - Automatic rescale slope/intercept application
  - Support for grayscale images
  - MedVision.Imaging.vcxproj - Static library project
  - README.md - Library documentation

#### Implementation Details
**DicomImage.h/cpp:**
- Extract image dimensions (width, height, bits allocated/stored)
- Extract pixel representation (signed/unsigned)
- Extract photometric interpretation
- Extract window/level defaults from DICOM tags
- Extract rescale slope/intercept
- Convenience methods for patient name, ID, study description, modality
- Pixel data extraction from DicomDataSet

**PixelDataProcessor.h/cpp:**
- Process 8-bit grayscale images
- Process 16-bit unsigned grayscale images
- Process 16-bit signed grayscale images
- Automatic rescale application using slope/intercept
- Convert pixel data to float buffers for processing

**WindowLevel.h/cpp:**
- Window/Level transformation algorithm
- Apply W/L to convert float pixels to 8-bit display values
- CT presets: Lung, Abdomen, Bone, Brain, Liver, Mediastinum
- Auto W/L from percentiles
- Configurable center and width

#### Build Status
- ? MedVision.Imaging builds successfully
- ? Links against MedVision.Dicom
- ? C++14 compliant
- ? Zero additional dependencies

### Planning Phase - 2024

#### Added - Documentation
- **MedVision_Viewer_Architecture.md** - Complete system architecture and design
  - Technology stack decisions (Win32 + DirectX 11 + ImGui)
  - Component architecture (MVC pattern)
  - 5-phase development roadmap (10 weeks)
  - Key classes and file structure
  - Performance targets and testing strategy

- **Phase1_Implementation.md** - Detailed implementation guide for Phase 1
  - Week-by-week task breakdown
  - Code templates and examples for all classes
  - DicomImage, PixelDataProcessor, WindowLevel implementation details
  - D3DContext, Texture2D, ImageRenderer implementation details
  - MainWindow with mouse interaction implementation
  - Testing checklist and troubleshooting guide

- **Project_Setup_Checklist.md** - Step-by-step project creation guide
  - Visual Studio project creation steps
  - Configuration settings for all projects
  - Folder structure setup
  - Build verification steps
  - Git workflow integration

- **Feature_Roadmap.md** - Comprehensive feature comparison with MicroDicom
  - 150+ features tracked across 9 categories
  - Priority assignments (P0-P3)
  - Phase allocation for each feature
  - Current status tracking (?/??/?/?)
  - Performance and quality metrics
  - Feature parity analysis (78% target)

- **Quick_Reference.md** - Daily development reference
  - Project status dashboard
  - Development timeline
  - Key files and locations
  - Common development tasks
  - Build commands and keyboard shortcuts
  - Troubleshooting guide
  - Code style guide
  - Resource links

- **Getting_Started.md** - Project onboarding guide
  - What's completed and what's next
  - Immediate action items
  - Documentation index
  - Project structure overview
  - Technology stack summary
  - Learning resources
  - Development checklist
  - Success criteria
  - Daily workflow suggestions

- **Solution_Structure.md** - Updated with viewer components
  - Added MedVision.Imaging structure
  - Added MedVision.Rendering structure
  - Added MedVision.Database structure
  - Added MedVision.Viewer structure
  - Documented technology decisions
  - Added development roadmap phases
  - Expanded namespace conventions

- **CHANGELOG.md** - This file, tracking project changes

#### Modified - Existing Files
- **.github/workflows/ci.yml** - Added commented-out build steps for future projects
  - Placeholder for MedVision.Imaging build
  - Placeholder for MedVision.Rendering build
  - Placeholder for MedVision.Viewer build
  - Placeholder for artifact upload

#### Projects Planned
- **MedVision.Imaging** - Image processing library (Phase 1, Week 1)
  - DicomImage class - DICOM image wrapper
  - PixelDataProcessor class - Pixel data extraction
  - WindowLevel class - W/L transformations
  - ImageBuffer class - Image data container

- **MedVision.Rendering** - GPU rendering library (Phase 1, Week 2)
  - D3DContext class - DirectX 11 device management
  - Texture2D class - GPU texture wrapper
  - Shader class - HLSL shader management
  - ImageRenderer class - 2D image rendering
  - HLSL shaders - Vertex and pixel shaders

- **MedVision.Database** - Local database library (Phase 3)
  - DicomDatabase class - SQLite wrapper
  - StudyQuery class - Query builder
  - Indexer class - Background file indexer
  - ThumbnailCache class - Thumbnail management

- **MedVision.Viewer** - Desktop application (Phase 1, Week 2)
  - Application class - Application lifecycle
  - MainWindow class - Main window implementation
  - ViewerPanel class - Image viewport
  - StudyBrowser class - Study tree view
  - ThumbnailPanel class - Thumbnail strip
  - TagViewer class - DICOM tag display

## [0.1.0] - Existing - MedVision.Dicom

### Completed (Before Viewer Planning)
- ? MedVision.Dicom library
  - DICOM file reading (DicomReader)
  - DICOM file writing (DicomWriter)
  - DICOM tag management (DicomTag, DicomDictionary)
  - Value Representation handling (VR, VRUtils)
  - Dataset management (DicomDataSet, DicomElement)
  - Transfer syntax support (TransferSyntax)
  - Explicit/Implicit VR support
  - Little/Big Endian byte order
  - 50+ common DICOM tags

- ? MedVision.Dicom.Tests
  - DicomTagTests - Tag creation and comparison
  - DicomElementTests - Element data storage
  - DicomDataSetTests - Dataset management
  - DicomReaderTests - File reading
  - DicomWriterTests - File writing
  - VRTests - VR utilities
  - IntegrationTests - End-to-end workflows

- ? Documentation
  - Docs/README.md - Project overview
  - Docs/Solution_Structure.md - Original structure (now updated)
  - MedVision.Dicom/README.md - Library documentation
  - MedVision.Dicom.Tests/docs/ - Test documentation

- ? CI/CD Pipeline
  - GitHub Actions workflow for build and test
  - Automated unit test execution
  - Test result artifact upload

## Roadmap

### Phase 1: Foundation (Weeks 1-2) - **NEXT**
**Status:** ?? Planning Complete, ? Implementation Not Started

**Deliverables:**
- [ ] MedVision.Imaging library
- [ ] MedVision.Rendering library
- [ ] MedVision.Viewer basic application
- [ ] Single DICOM file display
- [ ] Window/Level adjustment
- [ ] Pan and zoom functionality

**Expected Completion:** Week 2

### Phase 2: Core Features (Weeks 3-4)
**Status:** ? Planned

**Deliverables:**
- [ ] Series/Study management
- [ ] Thumbnail browser
- [ ] DICOM tag viewer
- [ ] Measurement tools (length, angle)
- [ ] ImGui integration

**Expected Completion:** Week 4

### Phase 3: Advanced Features (Weeks 5-6)
**Status:** ? Planned

**Deliverables:**
- [ ] MedVision.Database library
- [ ] Local SQLite database
- [ ] Multi-viewport layouts (1x2, 2x2, 2x3)
- [ ] Export to JPEG/PNG/BMP
- [ ] Print functionality
- [ ] Anonymization

**Expected Completion:** Week 6

### Phase 4: 3D/MPR (Weeks 7-8)
**Status:** ? Planned

**Deliverables:**
- [ ] Multi-planar reconstruction (MPR)
- [ ] 3D volume rendering
- [ ] Cine playback
- [ ] Advanced measurements
- [ ] Transfer function editor

**Expected Completion:** Week 8

### Phase 5: PACS Integration (Weeks 9-10)
**Status:** ? Planned

**Deliverables:**
- [ ] MedVision.Pacs library
- [ ] DICOM C-FIND (Query)
- [ ] DICOM C-MOVE (Retrieve)
- [ ] DICOM C-STORE (Send)
- [ ] PACS connection manager
- [ ] Remote study browser

**Expected Completion:** Week 10

### Future Phases (Beyond Week 10)
**Status:** ?? Ideas

**Potential Features:**
- [ ] Compression support (JPEG, JPEG 2000, RLE)
- [ ] Advanced image analysis tools
- [ ] Reporting integration
- [ ] DICOM Print (SCU)
- [ ] Worklist integration
- [ ] Storage SCP (receive images)
- [ ] Plugin system
- [ ] Scripting support

## Development Metrics

### Current Status (Planning Phase)
- **Lines of Code:** 0 (viewer components)
- **Test Coverage:** 0%
- **Documentation Pages:** 8 (viewer docs)
- **Features Implemented:** 0 / 116 planned (0%)
- **Build Status:** N/A (projects not created)
- **Tests Passing:** N/A

### Existing Status (MedVision.Dicom)
- **Lines of Code:** ~3000 (DICOM library)
- **Test Coverage:** ~80% (estimated)
- **Test Cases:** 50+ unit tests
- **Build Status:** ? Passing
- **Tests Passing:** ? All passing

## Notes

### Design Decisions
1. **Win32 + DirectX 11 over WPF**
   - Rationale: Maximum performance, GPU acceleration, full control
   - Trade-off: More complex UI code vs. XAML designer

2. **ImGui for UI widgets**
   - Rationale: Immediate mode, lightweight, good for tools
   - Trade-off: Less polished than native Windows controls

3. **SQLite for database**
   - Rationale: Embedded, zero-config, ACID compliant
   - Trade-off: Single-writer limitation

4. **C++14 standard**
   - Rationale: Consistency with existing MedVision.Dicom
   - Trade-off: Can't use C++17/20 features

### Future Considerations
- Consider upgrading to C++17 in Phase 3
- Evaluate OpenGL/Vulkan for cross-platform (Phase 6+)
- Consider Qt for richer UI (alternative to ImGui)
- Plan for internationalization (i18n)

## Contributors

- **Initial Planning & Architecture:** 2024
  - Complete documentation suite
  - 10-week implementation roadmap
  - Feature parity analysis with MicroDicom

## Repository

- **GitHub:** https://github.com/gaukem/MedVision
- **Branch:** main
- **License:** (To be determined)

---

## How to Update This Changelog

### When Adding Features
```markdown
### Added
- **FeatureName** - Brief description
  - Detail 1
  - Detail 2
```

### When Fixing Bugs
```markdown
### Fixed
- **BugDescription** - What was fixed and how
```

### When Making Changes
```markdown
### Changed
- **What changed** - Why it changed
```

### When Deprecating
```markdown
### Deprecated
- **FeatureName** - Will be removed in version X
```

### When Removing
```markdown
### Removed
- **FeatureName** - Why it was removed
```

---

**Changelog Version:** 1.0  
**Last Updated:** 2024  
**Next Review:** After Phase 1 completion
