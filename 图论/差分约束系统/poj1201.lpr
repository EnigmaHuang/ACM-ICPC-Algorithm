Const
  inf      = 'poj1201.txt';
  ouf      = 'poj1201ans.txt';
  PointNum = 50001;
  EdgeNum  = 50001*3+1000;
  Ondbg    = true;

Type
  TEdge = record
            trg,len,next:longint;
          end;

Var
  Edges   : array[1..EdgeNum]  of TEdge;
  First   : array[1..PointNum] of longint;
  Visited : array[1..PointNum] of boolean;
  Dist    : array[0..PointNum] of longint;
  Queue   : array[1..PointNum] of longint;

  N,M,EdgesNum:longint;

  head,tail:longint;

Procedure AddEdge(source,target,weight:longint);
begin
  inc(EdgesNum);
  Edges[EdgesNum].trg:=target;
  Edges[EdgesNum].len:=weight;
  Edges[EdgesNum].next:=First[source];
  First[source]:=EdgesNum;
end;

Procedure ReadData;
var
  i,a,b,weight:longint;
begin
  fillchar(First,SizeOf(First),0);

  n:=0;
  readln(m);
  for i:=1 to m do
  begin
    readln(a,b,weight);
    if b+1>n then n:=b+1;
    AddEdge(b+1,a,-weight);
  end;

  for i:=0 to n-1 do
  begin
    AddEdge(i,i+1,1);
    AddEdge(i+1,i,0);
  end;
end;

Procedure QueueOut(var pnt:longint);
begin
  inc(head);
  if head>PointNum then head:=head-PointNum;
  pnt:=Queue[head];
  Visited[pnt]:=false;
end;

Procedure QueueIn(pnt:longint);
begin
  inc(tail);
  if tail>PointNum then tail:=tail-PointNum;
  Queue[tail]:=pnt;
  Visited[pnt]:=true;
end;

Function QueueEmpty:boolean;
begin
  if head=tail then QueueEmpty:=true else QueueEmpty:=false;
end;

Procedure SPFA(start:longint);
var
  now,new,nowpos:longint;
begin
  fillchar(Dist,SizeOf(Dist),127);
  fillchar(Visited,SizeOf(Visited),false);

  head:=0;
  tail:=1;

  Queue[tail]:=start;
  Visited[start]:=true;
  Dist[start]:=0;

  while not QueueEmpty() do
  begin
    QueueOut(now);
    nowpos:=First[now];
    repeat
      new:=Edges[nowpos].trg;
      if Dist[new]>Dist[now]+Edges[nowpos].len then
      begin
        Dist[new]:=Dist[now]+Edges[nowpos].len;
        if not Visited[new] then QueueIn(new);
      end;
      nowpos:=Edges[nowpos].next;
    until nowpos=0;
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

  ReadData;
  SPFA(n);
  writeln(Dist[n]-Dist[0]);

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.
