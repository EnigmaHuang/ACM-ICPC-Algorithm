Const
  inf      = 'poj1364.txt';
  ouf      = 'poj1364ans.txt';
  PointNum = 100;
  EdgeNum  = 100;
  Ondbg    = true;

Type
  TEdge = record
            trg,len,next:longint;
          end;

Var
  Edges   : array[1..EdgeNum]  of TEdge;
  First   : array[0..PointNum] of longint;
  Visited : array[0..PointNum] of boolean;
  Times   : array[0..PointNum] of longint;
  Dist    : array[0..PointNum] of longint;
  Queue   : array[1..PointNum*2] of longint;

  N,M,EdgesNum:longint;
  ans:string;

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
  c:array[1..4] of char;
begin
  fillchar(First,SizeOf(First),0);
  EdgesNum:=0;

  readln(m);
  for i:=1 to m do
  begin
    read(a,b);
    read(c[1],c[2],c[3],c[4]);
    readln(weight);
    if c[2]='g' then AddEdge(a+b,a-1,-weight-1)
                else AddEdge(a-1,a+b,weight-1);
  end;
end;

Procedure QueueOut(var pnt:longint);
begin
  inc(head);
  if head>PointNum then head:=head-PointNum;
  pnt:=Queue[head];
  Visited[pnt]:=false;
end;

Function QueueIn(pnt:longint):boolean;
begin
  inc(tail);
  if tail>PointNum then tail:=tail-PointNum;
  Queue[tail]:=pnt;
  Visited[pnt]:=true;
  inc(Times[pnt]);
  if Times[pnt]>n+2 then QueueIn:=false else QueueIn:=true;
  //因为一开始手动将所有的节点入了一次队列，所以原来>n变成>n+1
end;

Function QueueEmpty:boolean;
begin
  if head=tail then QueueEmpty:=true else QueueEmpty:=false;
end;

Procedure SPFA(start:longint);
var
  now,new,i,nowpos:longint;
begin
  fillchar(Dist,SizeOf(Dist),0);
  fillchar(Visited,SizeOf(Visited),false);
  fillchar(Times,SizeOf(Times),0);

  head:=0;
  tail:=0;

  for i:=0 to n do QueueIn(i);

  while not QueueEmpty() do
  begin
    QueueOut(now);
    nowpos:=First[now];
    while nowpos<>0 do
    begin
      new:=Edges[nowpos].trg;
      if Dist[new]>Dist[now]+Edges[nowpos].len then
      begin
        Dist[new]:=Dist[now]+Edges[nowpos].len;
        if not Visited[new] then
          if QueueIn(new)=false then  //入队列，顺便检查是否有负环
          begin
            ans:='successful conspiracy';
            exit;
          end;
      end;
      nowpos:=Edges[nowpos].next;
    end;
  end;

  ans:='lamentable kingdom';
end;

Begin
  if Ondbg then
  begin
    Assign(input,inf);
    Reset(input);
    Assign(output,ouf);
    Rewrite(output);
  end;

  read(n);
  while n<>0 do
  begin
    ReadData;
    SPFA(1);
    read(n);
    writeln(ans);
  end;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.

