Const
  inf      = 'poj1932.txt';
  ouf      = 'poj1932ans.txt';
  Ondbg    = true;
  QueueLen = 12000;
  MaxPoint = 100;
  MaxEdge  = 10000;
Type
  TEdge = record
            trg,next:longint;
          end;

Var
  Edges   : array[1..MaxEdge]  of TEdge;
  First   : array[1..MaxPoint] of longint;
  Visited : array[1..MaxPoint] of boolean;
  Dist    : array[1..MaxPoint] of longint;  //Dist[n]表示到第n号房间最少获得多少能量，消耗则为负值
  Queue   : array[1..QueueLen] of longint;
  VisTime : array[1..MaxPoint] of longint;
  Energys : array[1..MaxPoint] of longint;
  Connect : array[1..MaxPoint,1..MaxPoint] of boolean;

  head,tail,EdgesNum,MaxTimeInQueue:longint;
  n:longint;

  NgtvCyc:boolean;


Procedure AddEdge(source,target:longint);
begin
  inc(EdgesNum);
  Edges[EdgesNum].trg:=target;
  Edges[EdgesNum].next:=First[source];
  First[source]:=EdgesNum;
end;

Procedure QueueOut(var pnt:longint);
begin
  inc(head);
  if head>QueueLen then head:=head-QueueLen;
  pnt:=Queue[head];
  Visited[pnt]:=false;
end;

Function QueueIn(pnt:longint):boolean; //有负环则入队失败，否则返回成功信息
begin
  inc(tail);
  if tail>QueueLen then tail:=tail-QueueLen;
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
  i,j,trg,trgnum:longint;
begin
  fillchar(Connect,SizeOf(Connect),false);
  fillchar(First,SizeOf(First),0);
  EdgesNum:=0;

  for i:=1 to n do
  begin
    read(Energys[i],trgnum);
    for j:=1 to trgnum do
    begin
      read(trg);
      AddEdge(i,trg);
      Connect[i,trg]:=true;
    end;
    readln;
  end;

  MaxTimeInQueue:=n;
end;

Procedure SPFA(start:longint);
var
  now,new,nowpos:longint;
begin
  fillchar(Dist,SizeOf(Dist),-127);
  fillchar(VisTime,SizeOf(VisTime),0);
  fillchar(Visited,SizeOf(Visited),false);

  head:=0;
  tail:=1;

  Queue[tail]:=start;
  Visited[start]:=true;
  Dist[start]:=100;

  NgtvCyc:=false;

  while not QueueEmpty() do
  begin
    QueueOut(now);
    nowpos:=First[now];
    while nowpos<>0 do
    begin
      new:=Edges[nowpos].trg;
      if  (Dist[new]<Dist[now]+Energys[new]) and (Dist[now]>0)               //更新后去到该房间有更多能量，并且来到当前房间能量大于0
      and (Connect[1,now]) and (Connect[now,new]) and (Connect[new,n]) then  //从起点到当前房间到新房间到出口都是连通的
      begin
        Dist[new]:=Dist[now]+Energys[new];
        if not Visited[new] then
          if QueueIn(new)=false then
          begin
            NgtvCyc:=true;
            exit;
          end;
      end;
      nowpos:=Edges[nowpos].next;
    end;
  end;
end;

Procedure Floyd;
var
  i,j,k:longint;
begin
  for k:=1 to n do
    for i:=1 to n do
      for j:=1 to n do
        Connect[i,j]:=(Connect[i,k] and Connect[k,j]) or Connect[i,j] or (i=j);
end;

Procedure Solve;
begin
  Floyd;     //判断连通性
  SPFA(1);   //求路径消耗
  if Connect[1,n] then      //如果起点能走到终点
  begin
    if Dist[n]>=0 then writeln('winnable')    //去到终点的能量消耗小于100则可以
    //如果检测到负环，并且负环上任意一点可以与起点和重点相连，则可以
    else if (NgtvCyc) then writeln('winnable')
                      else writeln('hopeless');
  end
  else writeln('hopeless'); //起点无法直接走到终点
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
  while n<>-1 do
  begin
    ReadData;
    Solve;
    read(n);
  end;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.
