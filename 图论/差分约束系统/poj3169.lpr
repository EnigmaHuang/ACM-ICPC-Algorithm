Const
  inf      = 'poj3169.txt';
  ouf      = 'poj3169ans.txt';
  PointNum = 1000;
  EdgeNum  = 30000;
  Ondbg    = true;

Type
  TEdge = record
            trg,len,next:longint;
          end;

Var
  Edges   : array[1..EdgeNum]  of TEdge;
  First   : array[1..PointNum] of longint;
  Visited : array[1..PointNum] of boolean;
  Dist    : array[1..PointNum] of longint;
  Queue   : array[1..PointNum] of longint;
  VisTime : array[1..PointNum] of longint;

  N,ML,MD:longint;

  head,tail,EdgesNum,MaxTimeInQueue,MaxRouteLen,MaxEdge:longint;
  NgtvCyc:boolean;

Procedure AddEdge(source,target,weight:longint);
begin
  inc(EdgesNum);
  Edges[EdgesNum].trg:=target;
  Edges[EdgesNum].len:=weight;
  Edges[EdgesNum].next:=First[source];
  First[source]:=EdgesNum;
end;

Procedure QueueOut(var pnt:longint);
begin
  inc(head);
  if head>PointNum then head:=head-PointNum;
  pnt:=Queue[head];
  Visited[pnt]:=false;
end;

Function QueueIn(pnt:longint):boolean; //true=succeed, false=negative cycle detectived.
begin
  inc(tail);
  if tail>PointNum then tail:=tail-PointNum;
  Queue[tail]:=pnt;
  Visited[pnt]:=true;
  inc(VisTime[pnt]);
  if VisTime[pnt]>MaxTimeInQueue then QueueIn:=false else QueueIn:=true;
end;

Function QueueEmpty:boolean;
begin
  if head=tail then QueueEmpty:=true else QueueEmpty:=false;
end;

Procedure ReadData;
var
  i,a,b,dis:longint;
begin
  fillchar(First,SizeOf(First),0);

  readln(N,ML,MD);

  MaxEdge:=0;

  for i:=1 to ML do
  begin
    readln(a,b,dis);
    AddEdge(a,b,dis);
    if dis>MaxEdge then MaxEdge:=dis;
  end;

  for i:=1 to MD do
  begin
    readln(a,b,dis);
    AddEdge(b,a,-dis);
  end;

  for i:=2 to n do
  begin
    AddEdge(i,1,0);    //Dist[1]-Dist[i]<=0
    AddEdge(i,i-1,0);  //Dist[i-1]-Dist[i]<=0
  end;

  MaxTimeInQueue:=N;
  MaxRouteLen:=MaxEdge*N;
end;

Procedure SPFA(start:longint);
var
  now,new,nowpos:longint;
begin
  fillchar(Dist,SizeOf(Dist),127);
  fillchar(VisTime,SizeOf(VisTime),0);

  head:=0;
  tail:=1;

  Queue[tail]:=start;
  Visited[start]:=true;
  Dist[start]:=0;

  NgtvCyc:=false;

  while not QueueEmpty() do
  begin
    QueueOut(now);
    nowpos:=First[now];
    repeat
      new:=Edges[nowpos].trg;
      if Dist[new]>Dist[now]+Edges[nowpos].len then
      begin
        Dist[new]:=Dist[now]+Edges[nowpos].len;
        if not Visited[new] then
          if QueueIn(new)=false then  //Negative cycle detectived
          begin
            NgtvCyc:=true;
            exit;
          end;
      end;
      nowpos:=Edges[nowpos].next;
    until nowpos=0;
  end;
end;

Procedure PrintAns;
begin
  if NgtvCyc then writeln(-1)
  else
  begin
    if Dist[n]>=MaxRouteLen then writeln(-2)
                            else writeln(Dist[n]);
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
  SPFA(1);
  PrintAns;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.

