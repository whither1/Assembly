.386
.model flat, stdcall
option casemap :none
 
include \masm32\include\windows.inc
include \masm32\macros\macros.asm
include \masm32\include\Fpu.inc
uselib kernel32, user32, masm32, comctl32, Fpu
 
WndProc PROTO :DWORD,:DWORD,:DWORD,:DWORD
Solver PROTO :TBYTE,:TBYTE,:TBYTE,:TBYTE,:DWORD
FindMidPoint PROTO :TBYTE,:TBYTE,:DWORD
Func PROTO :DWORD,:DWORD
 
TEST_DIALOG = 1000
TEST_BTN = 1001
IDC_EDT1 = 1002
IDC_EDT2 = 1003
IDC_EDT3 = 1006
IDC_EDT = 1009
 
.data?
  hInstance dd ?
  hWnd dd ?
  icce INITCOMMONCONTROLSEX <>
  point1 dt ?
  point2 dt ?
  eps dt ?
  iter_am dt ?
  answer dt ?
 
.code
start PROC
  LOCAL WSAStruct :WSADATA
 
  invoke WSAStartup, 0101h, addr WSAStruct
  .if eax != 0
    invoke MessageBox, 0, chr$("WSAStartup - ошибка"), offset err, MB_ICONERROR
    invoke ExitProcess,eax
    ret
  .endif
 
  mov icce.dwSize, SIZEOF INITCOMMONCONTROLSEX
  mov icce.dwICC, ICC_DATE_CLASSES or \
                  ICC_INTERNET_CLASSES or \
                  ICC_PAGESCROLLER_CLASS or \
                  ICC_COOL_CLASSES
 
  invoke InitCommonControlsEx, offset icce
 
  invoke GetModuleHandle, NULL
  mov hInstance, eax
 
  invoke DialogBoxParam, hInstance, TEST_DIALOG, 0, offset WndProc, 0
 
  call WSACleanup
 
  invoke ExitProcess,eax
ret
start ENDP
 
WndProc proc hWin :DWORD, uMsg :DWORD, wParam :DWORD, lParam :DWORD
  LOCAL buf[20] :byte
  switch uMsg
    case WM_INITDIALOG
      invoke SendMessage, hWin, WM_SETICON, 1, FUNC(LoadIcon, NULL, IDI_ASTERISK)
 
    case WM_COMMAND
      switch wParam
        case TEST_BTN
          invoke GetDlgItemText, hWin, IDC_EDT1, addr buf, 20
          FpuAtoFL addr buf, addr point1, DEST_MEM
          invoke GetDlgItemText, hWin, IDC_EDT2, addr buf, 20
          FpuAtoFL addr buf, addr point2, DEST_MEM
          invoke GetDlgItemText, hWin, IDC_EDT3, addr buf, 20
          FpuAtoFL addr buf, addr eps, DEST_MEM
          invoke GetDlgItemText, hWin, IDC_EDT, addr buf, 20
          FpuAtoFL addr buf, addr iter_am, DEST_MEM
          invoke Solver, iter_am, eps, point1, point2, addr answer
          invoke FpuFLtoA addr answer, 6, buf, SRC1_REAL or SRC2_DIMM
          invoke MessageBox, hwin, addr buf, chr$("Ответ"), 0
          ret
      endsw
    case WM_CLOSE
      exit_program:
      invoke EndDialog, hWin, 0
 
    endsw
 
  xor eax,eax
ret
WndProc ENDP

Solver proc iter_am :TBYTE, eps :TBYTE, point_l :TBYTE, point_r :TBYTE, result :DWORD
  LOCAL func_res1 :TBYTE, func_res2 :TBYTE
  .while eax == CMP_GREATER && iter_am > 0
    invoke FindMidPoint, point_l, point_r, addr result
    invoke Func, addr point_l, addr func_res1
    invoke Func, result, addr func_res2
    invoke FpuMul addr func_res1, addr func_res2, 0, SRC1_REAL or SRC2_REAL or DEST_FPU
    invoke FpuComp 0, 0, SRC1_FPU or SRC2_DIMM
    .if eax == CMP_GREATER || eax == CMP_EQU
      invoke FpuAdd result, 0, addr point_l, SRC1_REAL or SRC2_DIMM or DEST_MEM
    .else
      invoke FpuAdd result, 0, addr point_r, SRC1_REAL or SRC2_DIMM or DEST_MEM
    .endif
    invoke FpuComp result, addr eps, SRC1_REAL or SRC2_REAL
    invoke FpuSub addr iter_am, 1, addr iter_am, SRC1_REAL or SRC2_DIMM or DEST_MEM
  .endw
Solver ENDP

FindMidPoint proc left :TBYTE, right :TBYTE, result :DWORD
  invoke FpuAdd addr left, addr right, 0, SRC1_REAL or SRC2_REAL or DEST_FPU
  invoke FpuDiv 0, 2, result, SRC1_FPU or SRC2_DIMM or DEST_MEM
FindMidPoint ENDP

Func proc x :DWORD, y :DWORD
  invoke FpuMul x, x, 0, SRC1_REAL or SRC2_REAL or DEST_FPU
  invoke FpuMul 0, x, 0, SRC1_FPU or SRC2_REAL or DEST_FPU
  invoke FpuAdd 0, 7, 0, SRC1_FPU or SRC2_DIMM or DEST_FPU
  invoke FpuCos 0, y, SRC1_FPU or DEST_MEM
Func ENDP
END start