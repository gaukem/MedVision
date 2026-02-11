# MedVision.Viewer - Architecture & Implementation Plan

## Executive Summary
MedVision.Viewer is a desktop DICOM viewer application similar to MicroDicom, designed to provide comprehensive medical image viewing capabilities with an intuitive interface.

## Project Overview

### Target Features (Based on MicroDicom)
1. **Core Viewing Features**
   - Multi-format DICOM file support
   - 2D image rendering with windowing (W/L adjustment)
   - Multi-series and multi-study viewing
   - Thumbnail browser
   - DICOM tag viewer/editor
   - Measurement tools (length, angle, ROI)
   - Annotations and overlays

2. **Advanced Features**
   - Multi-planar reconstruction (MPR)
   - 3D volume rendering (VR)
   - Cine/movie playback for dynamic series
   - Export to standard formats (JPEG, PNG, BMP, AVI)
   - Print and DICOM print (DICOM Print SCU)
   - Anonymization tools
   - Batch processing

3. **PACS Integration**
   - DICOM network support (Query/Retrieve)
   - Worklist integration
   - DICOM Send (C-STORE)
   - Local DICOM database

## Technology Stack

### UI Framework Options
**Option A: Win32/DirectX (Recommended for Performance)**
- Direct Win32 API for window management
- DirectX 11/12 for GPU-accelerated rendering
- ImGui for UI components
- STB_image for thumbnail generation

**Option B: WPF/C# with C++ Core (Easier Development)**
- WPF for UI (XAML)
- C++/CLI wrapper around MedVision.Dicom
- WriteableBitmap for image display
- Better designer support

**Selected: Option A (Win32/DirectX + ImGui)**
- Best performance for medical imaging
- Full control over rendering pipeline
- GPU acceleration for MPR and 3D
- Consistent with C++ stack

### Core Dependencies
```
MedVision.Viewer (Win32 Application)
戍式式 MedVision.Dicom          ? DICOM I/O (Completed)
戍式式 MedVision.Imaging        ?? Image Processing (To Build)
戍式式 MedVision.Rendering      ?? GPU Rendering (To Build)
戍式式 MedVision.Database       ?? Local DICOM DB (To Build)
戍式式 MedVision.Pacs          ?? Network (Future)
戌式式 External Libraries:
    戍式式 DirectX 11/12        (Windows SDK)
    戍式式 ImGui               (UI widgets)
    戍式式 SQLite              (Local database)
    戌式式 STB libraries       (Image I/O)
```

## Architecture Design

### 1. Application Architecture (MVC Pattern)

```
忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖
弛           MedVision.Viewer.exe                  弛
弛                                                 弛
弛  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖  弛
弛  弛         Presentation Layer              弛  弛
弛  弛  - MainWindow (Win32)                   弛  弛
弛  弛  - ViewerPanel (DirectX)                弛  弛
弛  弛  - TagBrowser (ImGui)                   弛  弛
弛  弛  - ThumbnailPanel (ImGui)               弛  弛
弛  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎  弛
弛                    ∪                            弛
弛  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖  弛
弛  弛         Application Layer               弛  弛
弛  弛  - ViewerController                     弛  弛
弛  弛  - StudyManager                         弛  弛
弛  弛  - RenderingEngine                      弛  弛
弛  弛  - ToolManager (Measurements)           弛  弛
弛  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎  弛
弛                    ∪                            弛
弛  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖  弛
弛  弛         Domain Layer                    弛  弛
弛  弛  - DicomImage (Model)                   弛  弛
弛  弛  - Study/Series/Instance                弛  弛
弛  弛  - ImageProcessor                       弛  弛
弛  弛  - WindowLevelCalculator                弛  弛
弛  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎  弛
弛                    ∪                            弛
弛  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖  弛
弛  弛      Infrastructure Layer               弛  弛
弛  弛  - MedVision.Dicom (File I/O)          弛  弛
弛  弛  - MedVision.Imaging (Processing)       弛  弛
弛  弛  - MedVision.Rendering (GPU)            弛  弛
弛  弛  - DatabaseManager (SQLite)             弛  弛
弛  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎  弛
戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎
```

### 2. Key Components

#### 2.1 MedVision.Imaging Library (NEW)
**Purpose:** Image processing and manipulation
```
MedVision.Imaging/
戍式式 include/medvision/imaging/
弛   戍式式 DicomImage.h            # DICOM image wrapper
弛   戍式式 PixelDataProcessor.h    # Pixel data extraction
弛   戍式式 WindowLevel.h           # W/L calculations
弛   戍式式 LUT.h                   # Lookup tables
弛   戍式式 ImageFilters.h          # Filters (sharpen, smooth)
弛   戍式式 Measurements.h          # Length, angle, ROI
弛   戍式式 MPRGenerator.h          # Multi-planar reconstruction
弛   戌式式 VolumeRenderer.h        # 3D rendering
戌式式 src/                        # Implementations
```

**Key Classes:**
- `DicomImage`: Wraps DicomDataSet with pixel data access
- `PixelDataProcessor`: Handles decompression, rescale, modality LUT
- `WindowLevel`: Applies window/level transformations
- `ImageFilters`: Zoom, rotate, flip, filters

#### 2.2 MedVision.Rendering Library (NEW)
**Purpose:** GPU-accelerated rendering
```
MedVision.Rendering/
戍式式 include/medvision/rendering/
弛   戍式式 D3DRenderer.h           # DirectX 11 renderer
弛   戍式式 Texture2D.h             # GPU texture management
弛   戍式式 Shader.h                # HLSL shader wrapper
弛   戍式式 RenderTarget.h          # Render target management
弛   戌式式 VolumeRenderer.h        # 3D volume rendering
戌式式 src/
    戌式式 shaders/
        戍式式 basic_2d.hlsl       # 2D image display
        戍式式 window_level.hlsl   # W/L in shader
        戌式式 volume_raycasting.hlsl  # 3D rendering
```

#### 2.3 MedVision.Database Library (NEW)
**Purpose:** Local DICOM database for fast access
```
MedVision.Database/
戍式式 include/medvision/database/
弛   戍式式 DicomDatabase.h         # SQLite wrapper
弛   戍式式 StudyQuery.h            # Query builder
弛   戌式式 Indexer.h               # Background indexer
戌式式 sql/
    戌式式 schema.sql              # Database schema
```

**Schema:**
```sql
-- Patient table
CREATE TABLE Patients (
    PatientID TEXT PRIMARY KEY,
    PatientName TEXT,
    PatientBirthDate TEXT,
    PatientSex TEXT
);

-- Study table
CREATE TABLE Studies (
    StudyInstanceUID TEXT PRIMARY KEY,
    PatientID TEXT,
    StudyDate TEXT,
    StudyTime TEXT,
    StudyDescription TEXT,
    Modality TEXT,
    FOREIGN KEY (PatientID) REFERENCES Patients(PatientID)
);

-- Series table
CREATE TABLE Series (
    SeriesInstanceUID TEXT PRIMARY KEY,
    StudyInstanceUID TEXT,
    SeriesNumber INTEGER,
    SeriesDescription TEXT,
    Modality TEXT,
    FOREIGN KEY (StudyInstanceUID) REFERENCES Studies(StudyInstanceUID)
);

-- Instance table
CREATE TABLE Instances (
    SOPInstanceUID TEXT PRIMARY KEY,
    SeriesInstanceUID TEXT,
    InstanceNumber INTEGER,
    FilePath TEXT NOT NULL,
    Rows INTEGER,
    Columns INTEGER,
    FOREIGN KEY (SeriesInstanceUID) REFERENCES Series(SeriesInstanceUID)
);
```

#### 2.4 MedVision.Viewer Application
**Main Window Layout:**
```
忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖
弛 Menu Bar: File | View | Tools | Window | Help          弛
戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣
弛 Tool Bar: [Open] [Save] [W/L] [Zoom] [Measure] [...]  弛
戍式式式式式式式式式式成式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式成式式式式式式式式式式式扣
弛          弛                                 弛           弛
弛 Studies  弛       Main Viewport             弛  DICOM    弛
弛 Browser  弛                                 弛  Tags     弛
弛 (Tree)   弛    [DICOM Image Display]        弛  Viewer   弛
弛          弛                                 弛           弛
弛  + Study 弛         512x512                 弛  (0010,   弛
弛    - Ser 弛                                 弛   0010)   弛
弛      Img 弛    Window: 400 Level: 40        弛   Patient 弛
弛          弛                                 弛   Name    弛
弛          弛                                 弛           弛
戍式式式式式式式式式式扛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扛式式式式式式式式式式式扣
弛 Thumbnails: [img1] [img2] [img3] [img4] ...            弛
戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣
弛 Status: Ready | Patient: DOE^JOHN | 1/120              弛
戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎
```

## Implementation Phases

### Phase 1: Foundation (Weeks 1-2)
**Goal:** Basic viewer with single image display

**Deliverables:**
1. Create MedVision.Imaging library
   - DicomImage class
   - PixelDataProcessor (8-bit, 16-bit grayscale)
   - WindowLevel calculator
   - Basic LUT application

2. Create MedVision.Rendering library
   - D3D11 initialization
   - Texture2D wrapper
   - Basic 2D shader
   - Render loop

3. Create MedVision.Viewer application
   - Win32 window creation
   - File open dialog
   - Single image display
   - Mouse pan/zoom
   - Window/Level with mouse drag

**Success Criteria:**
- ? Open a DICOM file
- ? Display grayscale image
- ? Adjust window/level with mouse
- ? Pan and zoom

### Phase 2: Core Viewer Features (Weeks 3-4)
**Goal:** Multi-image support and basic tools

**Deliverables:**
1. Series/Study management
   - Study/Series/Instance model
   - Multi-image loader
   - Navigation (next/prev, scroll wheel)
   - Thumbnail generation

2. UI Framework (ImGui integration)
   - ImGui setup with DirectX
   - Study browser panel
   - DICOM tag viewer
   - Thumbnail strip

3. Basic tools
   - Measurement tool (distance)
   - Angle measurement
   - Text annotations
   - ROI (region of interest)

**Success Criteria:**
- ? Load entire series
- ? Navigate with keyboard/mouse wheel
- ? Display thumbnails
- ? Measure distances on image
- ? View DICOM tags

### Phase 3: Advanced Features (Weeks 5-6)
**Goal:** Professional viewer capabilities

**Deliverables:**
1. MedVision.Database integration
   - SQLite database setup
   - Background indexer
   - Study/Series queries
   - Fast thumbnail loading

2. Multi-viewport layouts
   - 1x1, 1x2, 2x2, 2x3 layouts
   - Synchronized scrolling
   - Independent W/L per viewport

3. Export and print
   - Export to JPEG/PNG/BMP
   - Copy to clipboard
   - Windows print dialog
   - Image annotations in export

**Success Criteria:**
- ? Fast study browser with database
- ? Multiple viewports
- ? Export images with annotations
- ? Print functionality

### Phase 4: Advanced Imaging (Weeks 7-8)
**Goal:** MPR and 3D capabilities

**Deliverables:**
1. Multi-planar reconstruction (MPR)
   - Volume builder from series
   - Axial/Sagittal/Coronal views
   - Oblique slicing
   - Synchronized cross-hair

2. 3D Volume Rendering
   - Ray-casting shader
   - Transfer function editor
   - Rotation controls
   - Preset rendering modes (MIP, MinIP, VR)

3. Advanced tools
   - Cine playback
   - Time-series analysis
   - Hounsfield unit (HU) display
   - Histogram equalization

**Success Criteria:**
- ? Generate MPR views
- ? Basic 3D volume rendering
- ? Cine playback
- ? HU measurements

### Phase 5: PACS Integration (Weeks 9-10)
**Goal:** Network capabilities

**Deliverables:**
1. MedVision.Pacs library
   - DICOM C-FIND (Query)
   - DICOM C-MOVE (Retrieve)
   - DICOM C-STORE (Send)
   - Connection manager

2. Viewer integration
   - PACS connection dialog
   - Remote study browser
   - Query interface
   - Send selected images to PACS

**Success Criteria:**
- ? Query remote PACS
- ? Retrieve studies
- ? Send images to PACS

## File Structure

```
MedVision.Viewer/
戍式式 src/
弛   戍式式 main.cpp                    # Application entry point
弛   戍式式 Application.cpp/h           # Application class
弛   戍式式 MainWindow.cpp/h            # Main window
弛   弛
弛   戍式式 UI/
弛   弛   戍式式 ViewerPanel.cpp/h       # Main viewport
弛   弛   戍式式 StudyBrowser.cpp/h      # Study tree view
弛   弛   戍式式 ThumbnailPanel.cpp/h    # Thumbnail strip
弛   弛   戍式式 TagViewer.cpp/h         # DICOM tag display
弛   弛   戍式式 ToolPanel.cpp/h         # Tool buttons
弛   弛   戌式式 Dialogs/
弛   弛       戍式式 OpenFileDialog.cpp/h
弛   弛       戍式式 SettingsDialog.cpp/h
弛   弛       戌式式 AboutDialog.cpp/h
弛   弛
弛   戍式式 Controllers/
弛   弛   戍式式 ViewerController.cpp/h  # Main controller
弛   弛   戍式式 StudyManager.cpp/h      # Study/Series management
弛   弛   戍式式 ToolController.cpp/h    # Tool management
弛   弛   戌式式 RenderController.cpp/h  # Rendering coordination
弛   弛
弛   戍式式 Models/
弛   弛   戍式式 Study.cpp/h             # Study model
弛   弛   戍式式 Series.cpp/h            # Series model
弛   弛   戍式式 Instance.cpp/h          # Instance model
弛   弛   戍式式 Viewport.cpp/h          # Viewport state
弛   弛   戌式式 Annotation.cpp/h        # Annotation data
弛   弛
弛   戌式式 Tools/
弛       戍式式 BaseTool.cpp/h          # Tool base class
弛       戍式式 WindowLevelTool.cpp/h   # W/L adjustment
弛       戍式式 MeasurementTool.cpp/h   # Length measurement
弛       戍式式 AngleTool.cpp/h         # Angle measurement
弛       戌式式 AnnotationTool.cpp/h    # Text annotation
弛
戍式式 resources/
弛   戍式式 icons/                      # UI icons
弛   戍式式 shaders/                    # HLSL shaders
弛   戌式式 app.rc                      # Windows resources
弛
戍式式 MedVision.Viewer.vcxproj
戌式式 README.md
```

## Development Guidelines

### Coding Standards
1. **C++ Version:** C++14 (consistent with MedVision.Dicom)
2. **Naming Convention:**
   - Classes: PascalCase (`DicomImage`)
   - Functions: PascalCase (`GetPixelData()`)
   - Variables: camelCase (`pixelData`)
   - Private members: trailing underscore (`data_`)
3. **Memory Management:**
   - Use smart pointers (`std::unique_ptr`, `std::shared_ptr`)
   - RAII for resource management
   - Avoid raw `new`/`delete`

### Performance Considerations
1. **Lazy Loading:** Load DICOM files on-demand
2. **Background Processing:** Use worker threads for:
   - DICOM file parsing
   - Database indexing
   - Thumbnail generation
3. **GPU Acceleration:** Move pixel operations to GPU shaders
4. **Caching:** Cache decoded pixel data and thumbnails

### Testing Strategy
1. **Unit Tests:**
   - Image processing algorithms
   - Window/Level calculations
   - Measurement accuracy
2. **Integration Tests:**
   - File loading
   - Database operations
   - Rendering pipeline
3. **Manual Testing:**
   - UI responsiveness
   - Real DICOM file compatibility
   - Performance with large series

## Next Steps

### Immediate Actions
1. ? Create this architecture document
2. ?? Create MedVision.Imaging project structure
3. ?? Create MedVision.Rendering project structure
4. ?? Create MedVision.Database project structure
5. ?? Create MedVision.Viewer project structure
6. ?? Set up DirectX 11 SDK references
7. ?? Integrate ImGui library
8. ?? Implement Phase 1 deliverables

### Documentation Updates
- Update `Docs/Solution_Structure.md` with new projects
- Create `Docs/User_Manual.md` for end users
- Create `Docs/Developer_Guide.md` for contributors
- Create `Docs/DICOM_Compliance.md` for conformance statement

## References
- DICOM Standard: https://www.dicomstandard.org/
- MicroDicom: https://www.microdicom.com/
- ImGui: https://github.com/ocornut/imgui
- DirectX 11 Programming Guide: https://docs.microsoft.com/en-us/windows/win32/direct3d11/

---
**Document Version:** 1.0  
**Last Updated:** 2024  
**Author:** MedVision Development Team
