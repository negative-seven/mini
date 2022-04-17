import pathlib
import subprocess

pathlib.Path('out/').mkdir(exist_ok=True)

result_compile = subprocess.run([
    'gcc',
    '-c',
    '-o', 'out/main.o',
    'src/main.c',
], check=True)

subprocess.run([
    'Crinkler.exe',
    '/OUT:out/out.exe',
    '/SUBSYSTEM:CONSOLE',
    '/ENTRY:WinMain',
    'out/main.o',
    'kernel32.lib',
    'user32.lib',
    'ucrt.lib',
    'gdi32.lib',
    'ntdll.lib',
], check=True)
