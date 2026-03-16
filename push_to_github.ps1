# Git Push Script for Student Management System

Write-Host "Setting up Git configuration..." -ForegroundColor Green
git config user.name "abdullah129026"
git config user.email "abdullahshaak@gmail.com"

Write-Host "`nChecking git status..." -ForegroundColor Green
git status

Write-Host "`nAdding all changes..." -ForegroundColor Green
git add .

Write-Host "`nCommitting changes..." -ForegroundColor Green
git commit -m "Refactor: Remove FileManager and fix compilation issues

- Deleted FileManager.h and FileManager.cpp (redundant)
- Fixed missing semicolons in Result.h and Class.h  
- Fixed ReportGenerator.h header guard
- Added includes and implementations to Fees.cpp
- Implemented Fees constructors, setters, and getters
- Fixed Result.cpp duplicate constructor and const signature
- Created main.cpp with menu interface
- Created Makefile for Windows build
- Added .gitignore

All file operations now handled by respective classes."

Write-Host "`nPushing to GitHub..." -ForegroundColor Green
git push origin main

Write-Host "`nDone!" -ForegroundColor Green
Start-Sleep -Seconds 2
