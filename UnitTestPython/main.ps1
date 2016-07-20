param([string]$Configuration)

echo "Running python unit tests against ${Configuration} configuration."

& python.exe main.py -c ${Configuration}

Remove-Item -Force _quadkey.pyd
Remove-Item -Force _quadkey.dll

