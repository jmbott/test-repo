Private Sub Worksheet_Change(ByVal Target As Range)

    Dim CCell(1 To 6) As String
    
    CCell(1) = "C9"
    CCell(2) = "C10"
    CCell(3) = "C15"
    CCell(4) = "C16"
    CCell(5) = "C21"
    CCell(6) = "C22"
    
    Dim ICell(1 To 6) As String
    
    ICell(1) = "I9"
    ICell(2) = "I10"
    ICell(3) = "I15"
    ICell(4) = "I16"
    ICell(5) = "I21"
    ICell(6) = "I22"

    For i = 1 To 6
       If Target.Address = Range(CCell(i)).Address Then
          a = ActiveSheet.Range(CCell(i)).Value
          Application.EnableEvents = False
          ActiveSheet.Range(ICell(i)).Value = a
       ElseIf Target.Address = Range(ICell(i)).Address Then
          a = ActiveSheet.Range(ICell(i)).Value
          Application.EnableEvents = False
          ActiveSheet.Range(CCell(i)).Value = a
       End If
       Application.EnableEvents = True
    Next i
End Sub
