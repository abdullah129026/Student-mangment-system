@echo off
cd StudentMS

echo ============================================
echo TESTING STUDENT MANAGEMENT SYSTEM
echo ============================================
echo.

REM Clear all data files
echo. > data\students.txt
echo. > data\attendance.txt
echo. > data\results.txt
echo. > data\fees.txt
echo. > data\classes.txt
echo. > data\enrollments.txt

echo Test Data Setup:
echo 1|John Smith|20|Male|10A|Main Street|5551234 >> data\students.txt
echo 2|Jane Doe|21|Female|10B|Oak Avenue|5555678 >> data\students.txt
echo 10A|Math Class|10|Mr. Johnson >> data\classes.txt
echo 10B|Science Class|10|Ms. Williams >> data\classes.txt
echo.
echo Data files created with test students and classes
echo.

pause
