Const
  MaxPointNum = 100;
  NoDirection = false;  //有向图
  inf='POJ1125.txt';

Var
  PointNum,EdgeNum,Start,Target:longint;
  EdgeMap:array[1..MaxPointNum,1..MaxPointNum] of longint; //存各边之间的权
  LinkTo:array[1..MaxPointNum,0..MaxPointNum] of longint;  //LinkTo[x,y]存与x点相连的第y条边，y=0时为边的总数
  Queue:array[0..MaxPointNum-1] of longint;                //待松弛队列
  Visited:array[1..MaxPointNum] of boolean;                //是否入队列
  Dist,Relay:array[1..MaxPointNum] of longint;             //到起点的最短路径，上一个中继点
  ans:array[1..MaxPointNum] of longint;            //各人作为传播源的结果
  head,tail:integer;

Procedure ReadData;
var
  i,j,EdgeStart,EdgeEnd,EdgeWeight:longint;
begin
  fillchar(LinkTo,SIzeOf(LinkTo),0);
  fillchar(EdgeMap,SizeOf(EdgeMap),1);
  readln(PointNum);
  for i:=1 to PointNum do
  begin
    EdgeStart:=i;
    read(EdgeNum);
    for j:=1 to EdgeNum do
    begin
      read(EdgeEnd,EdgeWeight);
      inc(LinkTo[EdgeStart,0]);
      LinkTo[EdgeStart,LinkTo[EdgeStart,0]]:=EdgeEnd;
      EdgeMap[EdgeStart,EdgeEnd]:=EdgeWeight;
    end;
  end;
end;

Procedure SPFA(start:integer);
var
  i,j,now:integer;
begin
  fillchar(Visited,sizeof(Visited),false);
  for j:=1 to PointNum do
  begin
    Dist[j]:=MaxLongint;
    Relay[j]:=j;
  end;
  Dist[start]:=0;
  Visited[start]:=true;
  now:=start;
  head:=0;
  tail:=1;
  Queue[tail]:=start;
  while head<>tail do
  begin
    Visited[now]:=false;
    head:=head+1;
    if head>MaxPointNum then head:=head-MaxPointNum; mod MaxPointNum;
    now:=Queue[head mod MaxPointNum];
    for i:=1 to LinkTo[now,0] do
      if dist[LinkTo[now,i]]>dist[now]+EdgeMap[now,LinkTo[now,i]] then
      begin
        dist[LinkTo[now,i]]:=dist[now]+EdgeMap[now,LinkTo[now,i]];
        relay[LinkTo[now,i]]:=now;
        if Visited[LinkTo[now,i]]=false then
        begin
          tail:=tail+1;
          if tail>MaxPointNum then tail:=tail-MaxPointNum;
          Queue[tail]:=LinkTo[now,i];
          Visited[LinkTo[now,i]]:=true;
        end;
      end;
  end;
end;

Procedure Solve;
var
  i,j,max,min,id:Longint;
begin
  if PointNum=0 then exit;
  for i:=1 to PointNum do
  begin
    SPFA(i);
    max:=0;
    for j:=1 to pointNum do if Dist[j]>max then max:=dist[j];
    ans[i]:=max;
  end;
  min:=MaxLongint;
  for i:=1 to PointNum do if ans[i]<min then
  begin
    min:=ans[i];
    id:=i;
  end;
  if min=MaxLongint then writeln('disjoint')
  else writeln(id,' ',min);
end;

Begin
  Assign(input,inf);
  Reset(input);
  repeat
    ReadData;
    Solve;
  until PointNum=0;
  Close(input);
End.

