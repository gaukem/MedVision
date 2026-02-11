# MedVision.Viewer - Feature Roadmap (MicroDicom Comparison)

## Overview
This document tracks feature parity with MicroDicom and defines implementation priorities.

## Feature Categories

### ? Completed | ?? In Progress | ? Planned | ? Not Planned

---

## Core Viewing Features

| Feature | MicroDicom | MedVision.Viewer | Priority | Phase | Status |
|---------|------------|------------------|----------|-------|--------|
| **File Operations** |
| Open DICOM file | ? | ?? | P0 | 1 | In Progress |
| Open folder | ? | ? | P0 | 2 | Planned |
| Recent files | ? | ? | P1 | 2 | Planned |
| Drag & drop | ? | ? | P1 | 2 | Planned |
| **Image Display** |
| Grayscale 8-bit | ? | ?? | P0 | 1 | In Progress |
| Grayscale 16-bit | ? | ?? | P0 | 1 | In Progress |
| Color (RGB) | ? | ? | P1 | 2 | Planned |
| Signed pixel data | ? | ?? | P0 | 1 | In Progress |
| **Window/Level** |
| Mouse drag W/L | ? | ?? | P0 | 1 | In Progress |
| Presets (Lung, Bone, etc.) | ? | ? | P1 | 1 | Planned |
| Custom W/L input | ? | ? | P1 | 2 | Planned |
| Auto W/L | ? | ?? | P1 | 1 | In Progress |
| **Navigation** |
| Pan with mouse | ? | ?? | P0 | 1 | In Progress |
| Zoom with wheel | ? | ?? | P0 | 1 | In Progress |
| Fit to window | ? | ? | P1 | 1 | Planned |
| 100% (1:1) zoom | ? | ? | P1 | 1 | Planned |
| Rotate 90¡Æ/180¡Æ/270¡Æ | ? | ? | P1 | 2 | Planned |
| Flip horizontal/vertical | ? | ? | P1 | 2 | Planned |
| **Series Management** |
| Browse series | ? | ? | P0 | 2 | Planned |
| Thumbnail view | ? | ? | P0 | 2 | Planned |
| Next/previous image | ? | ? | P0 | 2 | Planned |
| Keyboard navigation | ? | ? | P0 | 2 | Planned |
| Mouse wheel scrolling | ? | ? | P0 | 2 | Planned |

**Priority Legend:**
- **P0:** Critical (must-have)
- **P1:** High (should-have)
- **P2:** Medium (nice-to-have)
- **P3:** Low (future consideration)

---

## Measurement & Annotation Tools

| Feature | MicroDicom | MedVision.Viewer | Priority | Phase | Status |
|---------|------------|------------------|----------|-------|--------|
| **Measurements** |
| Length (ruler) | ? | ? | P0 | 2 | Planned |
| Angle | ? | ? | P0 | 2 | Planned |
| ROI (region of interest) | ? | ? | P1 | 2 | Planned |
| Ellipse ROI | ? | ? | P1 | 2 | Planned |
| Polygon ROI | ? | ? | P2 | 3 | Planned |
| Pixel value probe | ? | ? | P0 | 2 | Planned |
| Hounsfield unit (HU) | ? | ? | P1 | 2 | Planned |
| **Annotations** |
| Text annotation | ? | ? | P1 | 2 | Planned |
| Arrow | ? | ? | P1 | 2 | Planned |
| Free-hand drawing | ? | ? | P2 | 3 | Planned |
| Save annotations | ? | ? | P2 | 3 | Planned |
| **Overlays** |
| Patient info overlay | ? | ? | P1 | 2 | Planned |
| Scout line overlay | ? | ? | P2 | 4 | Planned |
| Scale/ruler overlay | ? | ? | P1 | 2 | Planned |

---

## Advanced Imaging

| Feature | MicroDicom | MedVision.Viewer | Priority | Phase | Status |
|---------|------------|------------------|----------|-------|--------|
| **Multi-Planar Reconstruction** |
| Axial/Sagittal/Coronal | ? | ? | P0 | 4 | Planned |
| Oblique MPR | ? | ? | P1 | 4 | Planned |
| Curved MPR | ? | ? | P3 | - | Not Planned (Phase 1) |
| Cross-hair sync | ? | ? | P1 | 4 | Planned |
| **3D Volume Rendering** |
| Ray-casting VR | ? | ? | P1 | 4 | Planned |
| Maximum Intensity Projection (MIP) | ? | ? | P1 | 4 | Planned |
| Minimum Intensity Projection (MinIP) | ? | ? | P2 | 4 | Planned |
| Surface rendering | ? | ? | P3 | - | Not Planned (Phase 1) |
| Transfer function editor | ? | ? | P2 | 4 | Planned |
| **Cine & Dynamic** |
| Cine playback | ? | ? | P1 | 4 | Planned |
| Speed control | ? | ? | P1 | 4 | Planned |
| Loop modes | ? | ? | P2 | 4 | Planned |
| Time-series analysis | ? | ? | P2 | 4 | Planned |

---

## User Interface

| Feature | MicroDicom | MedVision.Viewer | Priority | Phase | Status |
|---------|------------|------------------|----------|-------|--------|
| **Layout** |
| Single viewport | ? | ?? | P0 | 1 | In Progress |
| Multiple viewports (1x2, 2x2, etc.) | ? | ? | P0 | 3 | Planned |
| Customizable layout | ? | ? | P2 | 3 | Planned |
| Fullscreen mode | ? | ? | P1 | 2 | Planned |
| **Panels** |
| Study browser tree | ? | ? | P0 | 2 | Planned |
| Thumbnail panel | ? | ? | P0 | 2 | Planned |
| DICOM tag viewer | ? | ? | P0 | 2 | Planned |
| DICOM tag editor | ? | ? | P2 | 3 | Planned |
| Histogram panel | ? | ? | P2 | 3 | Planned |
| **Customization** |
| Toolbar customization | ? | ? | P2 | 3 | Planned |
| Theme/skin support | ? | ? | P3 | - | Not Planned (Phase 1) |
| Keyboard shortcuts | ? | ? | P1 | 2 | Planned |
| Mouse button mapping | ? | ? | P2 | 3 | Planned |

---

## Database & Organization

| Feature | MicroDicom | MedVision.Viewer | Priority | Phase | Status |
|---------|------------|------------------|----------|-------|--------|
| **Local Database** |
| SQLite database | ? | ? | P0 | 3 | Planned |
| Patient/Study/Series hierarchy | ? | ? | P0 | 3 | Planned |
| Fast search/filter | ? | ? | P0 | 3 | Planned |
| Background indexing | ? | ? | P1 | 3 | Planned |
| **File Management** |
| Watch folder (auto-import) | ? | ? | P2 | 3 | Planned |
| File organization | ? | ? | P2 | 3 | Planned |
| Duplicate detection | ? | ? | P2 | 3 | Planned |
| **Thumbnails** |
| Thumbnail cache | ? | ? | P0 | 3 | Planned |
| Fast thumbnail generation | ? | ? | P0 | 3 | Planned |

---

## Export & Print

| Feature | MicroDicom | MedVision.Viewer | Priority | Phase | Status |
|---------|------------|------------------|----------|-------|--------|
| **Export** |
| Export to JPEG | ? | ? | P0 | 3 | Planned |
| Export to PNG | ? | ? | P0 | 3 | Planned |
| Export to BMP | ? | ? | P0 | 3 | Planned |
| Export to TIFF | ? | ? | P2 | 3 | Planned |
| Export series as AVI | ? | ? | P2 | 4 | Planned |
| Export with annotations | ? | ? | P1 | 3 | Planned |
| Batch export | ? | ? | P2 | 3 | Planned |
| **Print** |
| Windows print dialog | ? | ? | P1 | 3 | Planned |
| Multi-image print | ? | ? | P2 | 3 | Planned |
| DICOM print (SCU) | ? | ? | P2 | 5 | Planned |
| Print preview | ? | ? | P2 | 3 | Planned |

---

## DICOM Networking (PACS)

| Feature | MicroDicom | MedVision.Viewer | Priority | Phase | Status |
|---------|------------|------------------|----------|-------|--------|
| **DICOM Services** |
| C-ECHO (verify connection) | ? | ? | P0 | 5 | Planned |
| C-FIND (query) | ? | ? | P0 | 5 | Planned |
| C-MOVE (retrieve) | ? | ? | P0 | 5 | Planned |
| C-STORE (send) | ? | ? | P0 | 5 | Planned |
| C-GET (alternative retrieve) | ? | ? | P2 | 5 | Planned |
| **PACS Integration** |
| AE title configuration | ? | ? | P0 | 5 | Planned |
| Multiple PACS servers | ? | ? | P1 | 5 | Planned |
| Query/Retrieve UI | ? | ? | P0 | 5 | Planned |
| Send selected images | ? | ? | P0 | 5 | Planned |
| **Worklist** |
| Modality worklist (C-FIND) | ? | ? | P2 | 5 | Planned |
| Worklist browser | ? | ? | P2 | 5 | Planned |
| **Storage SCP** |
| Receive images (C-STORE SCP) | ? | ? | P3 | - | Not Planned (Phase 1) |

---

## Image Processing

| Feature | MicroDicom | MedVision.Viewer | Priority | Phase | Status |
|---------|------------|------------------|----------|-------|--------|
| **Filters** |
| Sharpen | ? | ? | P2 | 3 | Planned |
| Smooth | ? | ? | P2 | 3 | Planned |
| Edge detection | ? | ? | P2 | 3 | Planned |
| Invert | ? | ? | P1 | 2 | Planned |
| **Enhancement** |
| Histogram equalization | ? | ? | P2 | 4 | Planned |
| CLAHE | ? | ? | P2 | 4 | Planned |
| Gamma correction | ? | ? | P2 | 3 | Planned |
| Pseudo-color (LUT) | ? | ? | P2 | 3 | Planned |
| **Analysis** |
| Histogram display | ? | ? | P2 | 3 | Planned |
| Profile plot | ? | ? | P2 | 3 | Planned |
| Statistics (min/max/mean) | ? | ? | P2 | 2 | Planned |

---

## Utilities

| Feature | MicroDicom | MedVision.Viewer | Priority | Phase | Status |
|---------|------------|------------------|----------|-------|--------|
| **DICOM Tools** |
| Anonymization | ? | ? | P1 | 3 | Planned |
| Tag editing | ? | ? | P2 | 3 | Planned |
| Tag dump to text | ? | ? | P2 | 2 | Planned |
| DICOM validation | ? | ? | P2 | 3 | Planned |
| **Conversion** |
| Convert to DICOM | ? | ? | P3 | - | Not Planned (Phase 1) |
| Convert from DICOM | ? | ? | P1 | 3 | Planned |
| Batch conversion | ? | ? | P2 | 3 | Planned |

---

## Performance & Quality

| Feature | MicroDicom | MedVision.Viewer | Priority | Phase | Target |
|---------|------------|------------------|----------|-------|--------|
| **Performance** |
| Fast file loading | ? | ?? | P0 | 1 | < 500ms for 512©÷ |
| Smooth W/L adjustment | ? | ?? | P0 | 1 | 60 FPS |
| GPU acceleration | ? | ?? | P0 | 1 | DirectX 11 |
| Multi-threading | ? | ? | P1 | 3 | Background loading |
| Memory efficiency | ? | ? | P1 | 3 | < 10MB per image |
| **Stability** |
| Error handling | ? | ? | P0 | All | Graceful degradation |
| Memory leak prevention | ? | ? | P0 | All | Smart pointers |
| Crash recovery | ? | ? | P2 | 3 | Save state |

---

## Supported Modalities

| Modality | Description | MicroDicom | MedVision.Viewer | Phase | Status |
|----------|-------------|------------|------------------|-------|--------|
| **Primary Support** |
| CT | Computed Tomography | ? | ?? | 1 | In Progress |
| MR | Magnetic Resonance | ? | ?? | 1 | In Progress |
| CR | Computed Radiography | ? | ?? | 1 | In Progress |
| DX | Digital Radiography | ? | ?? | 1 | In Progress |
| **Secondary Support** |
| US | Ultrasound | ? | ? | 2 | Planned |
| XA | X-Ray Angiography | ? | ? | 2 | Planned |
| MG | Mammography | ? | ? | 2 | Planned |
| PT | Positron Emission Tomography | ? | ? | 4 | Planned |
| NM | Nuclear Medicine | ? | ? | 4 | Planned |
| SC | Secondary Capture | ? | ? | 2 | Planned |
| **Future Support** |
| RF | Radio Fluoroscopy | ? | ? | 4 | Planned |
| ECG | Electrocardiography | ? | ? | - | Not Planned |
| SR | Structured Report | ? | ? | - | Not Planned |
| PR | Presentation State | ? | ? | - | Not Planned |

---

## Transfer Syntax Support

| Transfer Syntax | UID | MicroDicom | MedVision.Viewer | Phase | Status |
|-----------------|-----|------------|------------------|-------|--------|
| **Uncompressed** |
| Implicit VR Little Endian | 1.2.840.10008.1.2 | ? | ? | 1 | Implemented |
| Explicit VR Little Endian | 1.2.840.10008.1.2.1 | ? | ? | 1 | Implemented |
| Explicit VR Big Endian | 1.2.840.10008.1.2.2 | ? | ? | 1 | Implemented |
| **Compressed** |
| JPEG Baseline (Process 1) | 1.2.840.10008.1.2.4.50 | ? | ? | 3 | Planned |
| JPEG Lossless | 1.2.840.10008.1.2.4.70 | ? | ? | 3 | Planned |
| JPEG 2000 | 1.2.840.10008.1.2.4.90 | ? | ? | 3 | Planned |
| RLE Lossless | 1.2.840.10008.1.2.5 | ? | ? | 3 | Planned |

---

## Implementation Timeline

### Phase 1: Foundation (Weeks 1-2) ?? IN PROGRESS
- Basic file I/O
- Single image display
- Window/Level
- Pan/Zoom

**Delivered Features:** 5  
**Total Features:** ~150  
**Completion:** 3%

### Phase 2: Core Features (Weeks 3-4)
- Series navigation
- Thumbnail browser
- DICOM tag viewer
- Basic measurements

**Expected Completion:** 15%

### Phase 3: Advanced Features (Weeks 5-6)
- Database integration
- Multi-viewport
- Export functionality
- Anonymization

**Expected Completion:** 35%

### Phase 4: 3D/MPR (Weeks 7-8)
- Multi-planar reconstruction
- 3D volume rendering
- Cine playback
- Advanced measurements

**Expected Completion:** 55%

### Phase 5: PACS Integration (Weeks 9-10)
- Query/Retrieve
- C-STORE
- Worklist
- Network configuration

**Expected Completion:** 75%

### Future Phases (Beyond 10 weeks)
- Compression support
- Advanced analysis
- Clinical workflows
- Performance optimization

**Target Completion:** 90%+

---

## Feature Comparison Summary

| Category | MicroDicom | MedVision.Viewer (Target) | Current |
|----------|------------|---------------------------|---------|
| **Core Viewing** | ~40 features | ~35 features (88%) | 5 (12%) |
| **Measurements** | ~15 features | ~12 features (80%) | 0 (0%) |
| **Advanced Imaging** | ~15 features | ~10 features (67%) | 0 (0%) |
| **UI/UX** | ~20 features | ~15 features (75%) | 1 (5%) |
| **Database** | ~10 features | ~8 features (80%) | 0 (0%) |
| **Export/Print** | ~12 features | ~10 features (83%) | 0 (0%) |
| **PACS** | ~12 features | ~10 features (83%) | 0 (0%) |
| **Processing** | ~15 features | ~10 features (67%) | 0 (0%) |
| **Utilities** | ~10 features | ~6 features (60%) | 0 (0%) |
| **TOTAL** | ~149 features | ~116 features (78%) | 6 (4%) |

**Target Feature Parity:** 78% of MicroDicom functionality  
**Current Progress:** 4% complete  
**Estimated Time to Target:** 10 weeks (Phase 1-5)

---

## Differentiation Strategy

### Features Where MedVision.Viewer Will Excel

1. **Modern Architecture**
   - DirectX 11/12 GPU acceleration
   - Multi-threaded design
   - Modular, extensible codebase

2. **Open Source**
   - Full source code access
   - Community contributions
   - Educational value

3. **Developer-Friendly**
   - Clear API documentation
   - Plugin architecture (future)
   - Scripting support (future)

4. **Performance**
   - GPU-accelerated rendering
   - Optimized for large datasets
   - Real-time interaction

### Features We Won't Implement (Phase 1)

1. **Clinical Certification** - Research/educational tool only
2. **Advanced DICOM Services** - Storage SCP, Modality Performed Procedure Step
3. **Proprietary Formats** - Focus on DICOM standard
4. **Mobile Versions** - Desktop Windows only

---

## Quality Metrics

| Metric | MicroDicom | MedVision.Viewer Target |
|--------|------------|-------------------------|
| File load time (512©÷) | < 300ms | < 500ms |
| W/L responsiveness | < 10ms | < 16ms |
| Rendering FPS | 60 FPS | 60 FPS |
| Memory per image | ~5MB | < 10MB |
| Startup time | < 2s | < 2s |
| Supported formats | 50+ modalities | 10+ modalities (Phase 1-5) |

---

**Document Version:** 1.0  
**Last Updated:** 2024  
**Next Review:** After Phase 2 completion
