#!/usr/bin/env pwsh

Write-Host "=== Pushing to GitHub ===" -ForegroundColor Cyan
Write-Host "Repository: https://github.com/abdullah129026/Student-mangment-system.git" -ForegroundColor Yellow

# Set git credentials
git config user.name "abdullah129026"
git config user.email "abdullahshaak@gmail.com"

# Add all changes
git add -A

# Check if there are changes to commit
$status = git status --porcelain
if ($status) {
    Write-Host "Changes detected, committing..." -ForegroundColor Green
    git commit -m "Complete fix: All modules working with pipe-delimited file reading"
} else {
    Write-Host "No changes to commit" -ForegroundColor Yellow
}

# Push to GitHub using HTTPS with token
$token = "ghp_8ePjfx8Ouk7xRlX3Qy4wQIbWjhNDaH5YJgTa"
$username = "abdullah129026"
$repo = "https://github.com/abdullah129026/Student-mangment-system.git"

Write-Host "Pushing changes..." -ForegroundColor Green
git push https://${username}:${token}@github.com/${username}/Student-mangment-system.git main --force

if ($LASTEXITCODE -eq 0) {
    Write-Host "`n✓ SUCCESS! Changes pushed to GitHub!" -ForegroundColor Green
    Write-Host "Repository: https://github.com/abdullah129026/Student-mangment-system" -ForegroundColor Cyan
} else {
    Write-Host "`n✗ FAILED to push changes" -ForegroundColor Red
}
