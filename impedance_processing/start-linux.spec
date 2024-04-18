# -*- mode: python ; coding: utf-8 -*-

block_cipher = pyi_crypto.PyiBlockCipher(key='Jul?0701')


a = Analysis(['start.py'],
             pathex=['/home/incam/Documents/ilr/source_code.cee'],
             binaries=[],
             datas=[('./fonts', './reportlab/fonts')],
             hiddenimports=[],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher,
             noarchive=False)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          a.binaries,
          a.zipfiles,
          a.datas,
          [],
          name='imp_process',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          upx_exclude=[],
          runtime_tmpdir=None,
          console=False )
