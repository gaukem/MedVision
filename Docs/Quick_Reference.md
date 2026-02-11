# MedVision.Viewer - Quick Reference Guide

## Project Status Dashboard

| Component | Status | Progress | Notes |
|-----------|--------|----------|-------|
| MedVision.Dicom | ? Complete | 100% | Fully functional DICOM I/O |
| MedVision.Imaging | ? Complete | 100% | Phase 1 features done |
| MedVision.Rendering | ?? In Progress | 0% | Phase 1 Week 2 |
| MedVision.Viewer | ?? In Progress | 0% | Phase 1 Week 2 |
| MedVision.Database | ? Planned | 0% | Phase 3 |
| MedVision.Pacs | ? Planned | 0% | Phase 5 |

## Development Timeline

### Phase 1: Foundation (Weeks 1-2) - IN PROGRESS
**Goal:** Basic single-image viewer with W/L

- **Week 1:** MedVision.Imaging
  - [ ] Day 1-2: DicomImage, PixelDataProcessor
  - [ ] Day 3-4: WindowLevel, testing

- **Week 2:** Rendering & Viewer
  - [ ] Day 5-6: D3DContext, Texture2D, ImageRenderer
  - [ ] Day 7-9: MainWindow, mouse interactions
  - [ ] Day 10: Testing, documentation

**Success Criteria:**
- ? Open DICOM file
- ? Display with W/L adjustment
- ? Pan and zoom

### Phase 2: Core Features (Weeks 3-4)
**Goal:** Series navigation and tools

- Series/Study management
- Thumbnail browser
- Tag viewer
- Measurement tools

### Phase 3: Advanced Features (Weeks 5-6)
**Goal:** Database and multi-viewport

- Local SQLite database
- Multi-viewport layouts
- Export functionality

### Phase 4: 3D/MPR (Weeks 7-8)
**Goal:** Advanced imaging

- Multi-planar reconstruction
- 3D volume rendering
- Cine playback

### Phase 5: PACS (Weeks 9-10)
**Goal:** Network integration

- Query/Retrieve
- C-STORE

## Key Files & Locations

### Documentation
- **Architecture:** `Docs/MedVision_Viewer_Architecture.md`
- **Solution Structure:** `Docs/Solution_Structure.md`
- **Phase 1 Guide:** `Docs/Phase1_Implementation.md`
- **This File:** `Docs/Quick_Reference.md`

### Projects
- **MedVision.Dicom:** `MedVision.Dicom/MedVision.Dicom.vcxproj`
- **MedVision.Imaging:** `MedVision.Imaging/MedVision.Imaging.vcxproj` (to create)
- **MedVision.Rendering:** `MedVision.Rendering/MedVision.Rendering.vcxproj` (to create)
- **MedVision.Viewer:** `MedVision.Viewer/MedVision.Viewer.vcxproj` (to create)

### Key Classes (Phase 1)

#### MedVision.Imaging
```cpp
medvision::imaging::DicomImage       // DICOM image wrapper
medvision::imaging::PixelDataProcessor  // Pixel extraction
medvision::imaging::WindowLevel      // W/L transformations
```

#### MedVision.Rendering
```cpp
medvision::rendering::D3DContext     // DirectX 11 device
medvision::rendering::Texture2D      // GPU texture
medvision::rendering::ImageRenderer  // 2D rendering
```

#### MedVision.Viewer
```cpp
medvision::viewer::MainWindow        // Application window
```

## Build Configuration

### Prerequisites
- Visual Studio 2022
- Windows SDK 10.0+
- C++14 compiler

### Build Commands
```powershell
# Build all projects (Debug x64)
msbuild MedVision.sln /p:Configuration=Debug /p:Platform=x64 /m

# Build single project
msbuild MedVision.Viewer/MedVision.Viewer.vcxproj /p:Configuration=Debug /p:Platform=x64

# Run tests
vstest.console.exe bin\x64\Debug\MedVision.Dicom.Tests.dll
```

### Project Dependencies
```
MedVision.Viewer
戍式式 MedVision.Rendering
弛   戌式式 (DirectX 11 from Windows SDK)
戍式式 MedVision.Imaging
弛   戌式式 MedVision.Dicom
戌式式 MedVision.Dicom
```

## Common Development Tasks

### Task: Add New DICOM Tag Support
1. Add constant to `MedVision.Dicom/include/medvision/dicom/DicomTag.h`
2. Add dictionary entry to `MedVision.Dicom/src/DicomDictionary.cpp`
3. Add accessor to `DicomImage` if needed

### Task: Add New Window/Level Preset
1. Open `MedVision.Imaging/include/medvision/imaging/WindowLevel.h`
2. Add static method:
```cpp
static WindowLevel MyPreset() { return WindowLevel(center, width); }
```

### Task: Add New Measurement Tool
1. Create `MedVision.Viewer/src/Tools/MyTool.cpp/h`
2. Inherit from `BaseTool` (Phase 2)
3. Register in `ToolController`

### Task: Add New HLSL Shader
1. Create `.hlsl` file in `MedVision.Rendering/src/shaders/`
2. Add to vcxproj with FXC compile action
3. Load in `ImageRenderer` or custom renderer

## Testing Strategy

### Unit Tests
- Location: `MedVision.Dicom.Tests/`
- Run: Visual Studio Test Explorer or `vstest.console.exe`

### Integration Tests
- Test application: `MedVision.Imaging/tests/test_imaging.cpp`
- Manual viewer testing with sample DICOM files

### Test DICOM Files
Recommended test datasets:
- **8-bit grayscale:** CR (Computed Radiography)
- **16-bit signed:** CT (Computed Tomography)
- **16-bit unsigned:** MR (Magnetic Resonance)
- **Color:** US (Ultrasound), SC (Secondary Capture)

Download from:
- https://www.dicomlibrary.com/
- https://barre.dev/medical/samples/

## Keyboard Shortcuts (Phase 1)

| Shortcut | Action |
|----------|--------|
| Ctrl + O | Open file |
| Ctrl + W | Close file |
| Ctrl + Q | Quit application |
| Left Drag | Adjust Window/Level |
| Ctrl + Left Drag | Pan image |
| Mouse Wheel | Zoom in/out |

## Code Style Guide

### Naming Conventions
```cpp
// Classes: PascalCase
class DicomImage { };

// Functions: PascalCase
void ProcessPixelData();

// Variables: camelCase
int pixelCount = 0;

// Private members: trailing underscore
private:
    int width_;
    float zoom_;

// Constants: UPPER_CASE or kPascalCase
const int MAX_SIZE = 1024;
static const float kDefaultZoom = 1.0f;
```

### File Organization
```cpp
// Header file structure
#pragma once

// System includes
#include <vector>
#include <string>

// External library includes
#include <d3d11.h>

// Project includes
#include "medvision/dicom/DicomTag.h"

namespace medvision {
namespace imaging {

class MyClass {
public:
    // Public interface
    
private:
    // Private implementation
};

} // namespace imaging
} // namespace medvision
```

## Performance Targets

| Metric | Target | Notes |
|--------|--------|-------|
| File load time | < 500ms | 512x512 16-bit image |
| Rendering FPS | 60 FPS | Smooth viewport updates |
| W/L responsiveness | < 16ms | Per mouse move event |
| Memory per image | < 10MB | Excluding pixel data |
| Startup time | < 2s | Cold start |

## Troubleshooting

### Build Errors

**Error:** Cannot find DirectX headers
- **Solution:** Install Windows SDK 10.0 or later

**Error:** Unresolved external symbols from MedVision.Dicom
- **Solution:** Add project reference or link .lib file

**Error:** Shader compilation failed
- **Solution:** Check HLSL syntax, ensure FXC is configured in project

### Runtime Errors

**Error:** Black screen when rendering
- **Solution:** Check display buffer creation, verify W/L applied

**Error:** Crash on file open
- **Solution:** Verify file has pixel data, check for null pointers

**Error:** Image appears garbled
- **Solution:** Check byte order, verify bits allocated/stored

## Resource Links

### DICOM Standard
- Official Standard: https://www.dicomstandard.org/
- DICOM Tags: https://dicom.nema.org/medical/dicom/current/output/chtml/part06/chapter_6.html
- Transfer Syntaxes: https://dicom.nema.org/medical/dicom/current/output/chtml/part05/chapter_10.html

### DirectX 11
- Programming Guide: https://docs.microsoft.com/en-us/windows/win32/direct3d11/
- HLSL Reference: https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/

### Libraries
- ImGui: https://github.com/ocornut/imgui
- SQLite: https://www.sqlite.org/
- STB: https://github.com/nothings/stb

### Reference Viewers
- MicroDicom: https://www.microdicom.com/
- Horos: https://horosproject.org/
- 3D Slicer: https://www.slicer.org/

## Git Workflow

### Branch Strategy
```
main                    # Stable releases
戍式式 develop            # Integration branch
戍式式 feature/imaging    # MedVision.Imaging development
戍式式 feature/rendering  # MedVision.Rendering development
戌式式 feature/viewer     # MedVision.Viewer development
```

### Commit Message Format
```
[Component] Brief description

Detailed explanation if needed

- Bullet point 1
- Bullet point 2
```

Example:
```
[Imaging] Implement WindowLevel class

Added WindowLevel class for W/L transformations with common presets.

- Added Apply() method
- Added static preset methods (Lung, Bone, Brain, Abdomen)
- Implemented FromPercentiles() for auto W/L
```

## CI/CD Pipeline

Current GitHub Actions workflow:
- **File:** `.github/workflows/ci.yml`
- **Triggers:** Push to main, pull requests
- **Steps:**
  1. Build MedVision.Dicom
  2. Build MedVision.Dicom.Tests
  3. Run unit tests
  4. Upload test results

To extend for viewer:
1. Add build steps for new projects
2. Add artifact upload for .exe
3. Consider adding code coverage

## Contact & Support

- **GitHub Repository:** https://github.com/gaukem/MedVision
- **Issues:** https://github.com/gaukem/MedVision/issues
- **Documentation:** `Docs/` folder in repository

---
**Last Updated:** 2024
**Maintained By:** MedVision Development Team
