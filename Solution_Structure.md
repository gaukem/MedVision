
# MedVision – Solution Structure

This document describes the recommended Visual Studio solution layout for MedVision.

## Solution Layout
MedVision/
├─ MedVision.Dicom/        # DICOM parsing and IO
├─ MedVision.Imaging/     # 2D/3D imaging pipeline
├─ MedVision.Pacs/        # PACS communication
├─ MedVision.Viewer/      # Desktop viewer application
├─ MedVision.Common/      # Math, threading, logging
└─ docs/                  # Technical documentation

## Namespace Convention
medvision::dicom
medvision::imaging
medvision::pacs
medvision::viewer
medvision::common

## Visual Studio Notes
- Prefer static libraries for core modules
- Keep UI isolated from DICOM logic
- Focus on performance and memory usage

## GitHub Copilot Usage
- Assist with parsing logic
- Generate rendering pipeline skeletons
- Draft test cases and docs
