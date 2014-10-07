Const
  inf   = 'poj1258.txt';
  ouf   = 'poj1258ans.txt';
  Ondbg = true;
  PointNum = 100;
  EdgeNum  = PointNum*PointNum;

Type
  TEdge = record
            trg,len:longint;
          end;

Var
  Edges  : array[1..EdgeNum]  of TEdge;
  First  : array[1..PointNum] of longint;
  Next   : array[1..EdgeNum]  of longint;
  Heap   : array[1..PointNum] of TEdge;
  PntPos : array[1..PointNum] of longint;

  N,HeapTail,answer:longint;   //n为点的数目, m为边的数目
  EdgesNum:longint;

Procedure AddEdge(source,target,weight:longint);
begin
  inc(EdgesNum);
  Edges[EdgesNum].trg:=target;
  Edges[EdgesNum].len:=weight;
  Next[EdgesNum]:=First[source];
  First[source]:=EdgesNum;
end;

Procedure ReadData;
var
  i,source,target,weight:longint;
begin
  //下面两行应该去掉的，因为调试器初始化的问题，需要加上这两行让调试器顺利运行
  i:=1;
  First[i]:=1;

  fillchar(First,SizeOf(First),0);
  fillchar(Edges,SizeOf(Edges),0);
  fillchar(Next,SizeOf(Next),0);

  EdgesNum:=0;

  readln(N);

  for source:=1 to N do
  begin
    for target:=1 to N do
    begin
      read(weight);
      if weight<>0 then AddEdge(source,target,weight);
    end;
    readln;
  end;
end;

Procedure GoUp(j:longint);
var
  i:longint;
  x:TEdge;
begin
  x:=Heap[j];
  while j>1 do
  begin
    i:=j div 2;
    if Heap[i].len<=x.len then break;
    Heap[j]:=Heap[i];
    PntPos[Heap[j].trg]:=j;
    j:=i;
  end;
  Heap[j]:=x;
  PntPos[x.trg]:=j;
end;

Procedure GoDown(i:longint);
var
  x:TEdge;
  j:longint;
begin
  x:=Heap[i];
  while i*2<=HeapTail do
  begin
    j:=i*2;
    if (j<HeapTail) and (Heap[j+1].len<Heap[j].len) then inc(j);
    if x.len<=Heap[j].len then break;
    Heap[i]:=Heap[j];
    PntPos[Heap[i].trg]:=i;
    i:=j;
  end;
  Heap[i]:=x;
  PntPos[x.trg]:=i;
end;

Procedure Pop(var point,len:longint);
begin
  point:=Heap[1].trg;
  len:=Heap[1].len;
  PntPos[point]:=-1;
  Heap[1]:=Heap[HeapTail];
  PntPos[Heap[1].trg]:=1;
  Dec(HeapTail);
  GoDown(1);
end;

Procedure Prim;
var
  newpnt,cost:longint;
  i,j,now,new:longint;
  x:TEdge;
begin
  for i:=1 to n do
  begin
    Heap[i].trg:=i;
    Heap[i].len:=maxlongint;
    PntPos[i]:=i;
  end;
  Heap[1].len:=0;

  answer:=0;
  HeapTail:=n;

  for i:=1 to n do
  begin
    Pop(newpnt,cost);
    inc(answer,cost);
    now:=First[newpnt];
    repeat
      new:=Edges[now].trg;
      if (PntPos[new]<>-1) and (Edges[now].len<Heap[PntPos[new]].len) then
      begin
        Heap[PntPos[new]].len:=Edges[now].len;
        GoUp(PntPos[new]);
      end;
      now:=Next[now];
    until now=0;
  end;
end;

Begin
  if Ondbg then
  begin
    Assign(input,inf);
    Reset(input);
    Assign(output,ouf);
    Rewrite(output);
  end;

  while not eof(input) do
  begin
    ReadData;
    Prim;
    writeln(answer);
  end;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.


