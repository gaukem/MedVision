
# MedVision – Solution Structure

This document describes the recommended Visual Studio solution layout for MedVision.

## Solution Layout
MedVision/
├─ MedVision.Dicom/        # ✅ DICOM parsing and IO (COMPLETE)
├─ MedVision.Imaging/      # ✅ Image processing pipeline (COMPLETE - Phase 1)
├─ MedVision.Rendering/    # ⚠️ GPU rendering engine (IN PROGRESS)
├─ MedVision.Database/     # ⏳ Local DICOM database (PLANNED)
├─ MedVision.Pacs/         # ⏳ PACS communication (PLANNED)
├─ MedVision.Viewer/       # ⚠️ Desktop viewer application (IN PROGRESS)
├─ MedVision.Common/       # ⏳ Math, threading, logging (PLANNED)
└─ Docs/                   # ✅ Technical documentation

## MedVision.Dicom Structure (Completed)
```
MedVision.Dicom/
├── include/medvision/dicom/
│   ├── DicomTag.h              # DICOM tag representation
│   ├── VR.h                    # Value Representations
│   ├── DicomElement.h          # Data element
│   ├── DicomDataSet.h          # Element container
│   ├── DicomReader.h           # File reader
│   ├── DicomWriter.h           # File writer
│   ├── DicomDictionary.h       # Tag dictionary
│   └── TransferSyntax.h        # Transfer syntax utilities
├── src/                        # Implementation files (8 .cpp)
├── tests/                      # Example usage
├── MedVision.Dicom.vcxproj     # Visual Studio project
└── README.md                   # Documentation
```

### Key Features
- Zero external dependencies (C++ STL only)
- Static library (.lib)
- C++14 compliant
- Supports Explicit/Implicit VR
- Little/Big Endian byte order
- 60+ common DICOM tags (including Window/Level and Rescale parameters)

## MedVision.Imaging Structure (Complete - Phase 1)
```
MedVision.Imaging/
├── include/medvision/imaging/
│   ├── DicomImage.h              # ✅ DICOM image wrapper
│   ├── PixelDataProcessor.h      # ✅ Pixel data extraction (8/16-bit)
│   └── WindowLevel.h             # ✅ Window/Level calculations
├── src/
│   ├── DicomImage.cpp            # ✅ Implementation
│   ├── PixelDataProcessor.cpp    # ✅ Implementation
│   └── WindowLevel.cpp           # ✅ Implementation
├── MedVision.Imaging.vcxproj     # Visual Studio project
└── README.md                     # Documentation
```

### Key Features (Implemented)
- ✅ 8-bit grayscale image support
- ✅ 16-bit signed/unsigned grayscale support
- ✅ Window/Level transformations
- ✅ Rescale slope/intercept handling
- ✅ CT presets (Lung, Abdomen, Bone, Brain, Liver, Mediastinum)
- ✅ Auto W/L from percentiles
- ✅ Patient/Study information extraction

### Planned Features (Future Phases)
- ⏳ Color (RGB) image support
- ⏳ Modality LUT application
- ⏳ Image filters (sharpen, smooth, edge)
- ⏳ Measurements (length, angle, ROI)
- ⏳ MPR volume generation

## MedVision.Rendering Structure (In Progress)
```
MedVision.Rendering/
├── include/medvision/rendering/
│   ├── D3DRenderer.h             # DirectX 11 renderer
│   ├── Texture2D.h               # GPU texture management
│   ├── Shader.h                  # HLSL shader wrapper
│   ├── RenderTarget.h            # Render target management
│   └── VolumeRenderer.h          # 3D volume ray-casting
└── src/
    └── shaders/
        ├── basic_2d.hlsl         # 2D image display
        ├── window_level.hlsl     # W/L in shader
        └── volume_raycasting.hlsl # 3D rendering
```

### Key Features
- Hardware-accelerated rendering via DirectX 11
- Real-time window/level in GPU shader
- Texture streaming for large images
- 3D volume ray-casting
- Multi-viewport support

## MedVision.Database Structure (In Progress)
```
MedVision.Database/
├── include/medvision/database/
│   ├── DicomDatabase.h           # SQLite wrapper
│   ├── StudyQuery.h              # Query builder
│   ├── Indexer.h                 # Background file indexer
│   └── ThumbnailCache.h          # Thumbnail management
├── sql/
│   └── schema.sql                # Database schema (Patient/Study/Series/Instance)
└── src/                          # Implementation files
```

### Key Features
- SQLite-based local database
- DICOM hierarchy (Patient/Study/Series/Instance)
- Background file system indexer
- Fast study/series queries
- Thumbnail caching

## MedVision.Viewer Structure (In Progress)
```
MedVision.Viewer/
├── src/
│   ├── main.cpp                  # Application entry point
│   ├── Application.cpp/h         # Application class
│   ├── MainWindow.cpp/h          # Main window (Win32)
│   ├── UI/                       # UI components
│   │   ├── ViewerPanel.cpp/h     # Main image viewport
│   │   ├── StudyBrowser.cpp/h    # Study tree view
│   │   ├── ThumbnailPanel.cpp/h  # Thumbnail strip
│   │   └── TagViewer.cpp/h       # DICOM tag display
│   ├── Controllers/              # Application logic
│   │   ├── ViewerController.cpp/h
│   │   ├── StudyManager.cpp/h
│   │   └── ToolController.cpp/h
│   ├── Models/                   # Domain models
│   │   ├── Study.cpp/h
│   │   ├── Series.cpp/h
│   │   └── Instance.cpp/h
│   └── Tools/                    # Viewer tools
│       ├── WindowLevelTool.cpp/h
│       ├── MeasurementTool.cpp/h
│       └── AnnotationTool.cpp/h
├── resources/
│   ├── icons/                    # UI icons
│   ├── shaders/                  # HLSL shaders
│   └── app.rc                    # Windows resources
└── MedVision.Viewer.vcxproj
```

### Key Features
- Win32 native application
- DirectX 11 rendering with ImGui UI
- Multi-viewport layouts (1x1, 1x2, 2x2, 2x3)
- Window/Level adjustment
- Measurement tools (length, angle, ROI)
- DICOM tag viewer/editor
- Export to JPEG/PNG/BMP
- Study/Series browser with thumbnails

## Namespace Convention
- `medvision::dicom` - DICOM I/O
- `medvision::imaging` - Image processing
- `medvision::rendering` - GPU rendering
- `medvision::database` - Local database
- `medvision::pacs` - Network/PACS
- `medvision::viewer` - Viewer application
- `medvision::common` - Utilities

## Visual Studio Notes
- Prefer static libraries for core modules (.lib)
- Keep UI isolated from DICOM/imaging logic
- Focus on performance and memory usage
- Use DirectX 11 SDK (Windows SDK 10.0+)
- Link against: d3d11.lib, dxgi.lib, d3dcompiler.lib

## Technology Decisions

### UI Framework: Win32 + ImGui
- **Rationale:** Maximum performance, GPU acceleration, full control
- **Alternative considered:** WPF (rejected due to performance overhead)

### Rendering: DirectX 11
- **Rationale:** Native Windows, mature API, compute shader support
- **Alternative considered:** OpenGL (rejected for Windows-focused project)

### Database: SQLite
- **Rationale:** Embedded, zero-config, ACID compliant
- **Alternative considered:** JSON files (rejected for query performance)

## Development Roadmap

### Phase 1: Foundation (Weeks 1-2) - IN PROGRESS
- ✅ MedVision.Imaging: Basic image processing (COMPLETE)
- ⚠️ MedVision.Rendering: DirectX 11 setup (NEXT)
- ⚠️ MedVision.Viewer: Single image display with W/L (NEXT)

### Phase 2: Core Features (Weeks 3-4)
- Series/Study management
- Thumbnail browser
- DICOM tag viewer
- Basic measurement tools

### Phase 3: Advanced Features (Weeks 5-6)
- MedVision.Database integration
- Multi-viewport layouts
- Export functionality

### Phase 4: 3D/MPR (Weeks 7-8)
- Multi-planar reconstruction
- 3D volume rendering
- Cine playback

### Phase 5: PACS (Weeks 9-10)
- MedVision.Pacs library
- Query/Retrieve
- C-STORE support

## Documentation
- `Docs/MedVision_Viewer_Architecture.md` - Detailed viewer architecture
- `Docs/User_Manual.md` - End user guide (TBD)
- `Docs/Developer_Guide.md` - Developer documentation (TBD)
- `Docs/DICOM_Compliance.md` - Conformance statement (TBD)

## GitHub Copilot Usage
- Assist with DirectX 11 rendering code
- Generate HLSL shaders
- Draft ImGui UI layouts
- Create measurement algorithms
- Generate test cases and documentation
