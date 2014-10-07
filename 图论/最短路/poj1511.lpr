Const
  MaxPointNum = 1000005 ;
  QueueLength = 1000005 ;

Type
  EdgePointer = ^Edge;
  Edge = record
           src,tgr:longint;
           weight:int64;
           next:EdgePointer;
         end;
  TEdgeArray=array[1..MaxPointNum] of EdgePointer;



Var
  fEdges,bEdges:TEdgeArray;
  Queue:array[1..QueueLength] of longint;     //待松弛队列
  Visited:array[1..MaxPointNum] of boolean;   //是否入队列
  Dist:array[1..MaxPointNum] of int64;        //到起点的最短路径，上一个中继点

  head,tail:longint;
  answer:longint;
  N,P,Q,ii:longint;

Procedure ReadData;
var
  i,source,target:longint;
  price:int64;
  fEdge,bEdge:EdgePointer;
begin
  readln(P,Q);

  for i:=1 to P do
  begin
    fEdges[i]:=nil;
    bEdges[i]:=nil;
  end;

  for i:=1 to Q do
  begin
    readln(source,target,price);
    New(fEdge);
    New(bEdge);

    fEdge^.next:=fEdges[source];  //在队头插入
    fEdge^.src:=source;           //正向图
    fEdge^.tgr:=target;
    fEdge^.weight:=price;
    fEdges[source]:=fEdge;        //队头指向新的元素

    bEdge^.next:=bEdges[target];  //在队头插入
    bEdge^.src:=target;           //反向图
    bEdge^.tgr:=source;
    bEdge^.weight:=price;
    bEdges[target]:=bEdge;        //队头指向新的元素
  end;
end;

Procedure FreeMemory(var Edges:TEdgeArray);
var
  i:longint;
  p1,p2:EdgePointer;
begin
  for i:=1 to P do
  begin
    p1:=Edges[i];
    if p1=nil then continue;
    repeat
      p2:=p1;
      p1:=p1^.next;
      Dispose(p2);
    until p1=nil;
  end;
end;

Procedure SPFA(var Edges:TEdgeArray;start:integer);
var
  i,j,now,new:integer;
  p:EdgePointer;
begin
  fillchar(Visited,sizeof(Visited),false);
  fillchar(Dist,SizeOf(Dist),1);

  Dist[start]:=0;
  Visited[start]:=true;
  head:=0;
  tail:=1;
  Queue[tail]:=start;

  while head<>tail do
  begin
    head:=head+1;
    if head>QueueLength then head:=head-QueueLength;
    now:=Queue[head];
    Visited[now]:=false;
    p:=Edges[now];          //同一出发点，取队头元素(第一条边)开始枚举
    if p=nil then continue;
    repeat
      new:=p^.tgr;
      if dist[new]>dist[now]+p^.weight then
      begin
        dist[new]:=dist[now]+p^.weight;
        if Visited[new]=false then
        begin
          tail:=tail+1;
          if tail>QueueLength then tail:=tail-QueueLength;
          Queue[tail]:=new;
          Visited[new]:=true;
        end;
      end;
      p:=p^.next;           //取下一条边
    until p=nil;
  end;
  FreeMemory(Edges);
end;

Procedure Solve;
var
  i:longint;
begin
  answer:=0;
  SPFA(fEdges,1);
  for i:=2 to P do answer:=answer+Dist[i];
  SPFA(bEdges,1);
  for i:=2 to P do answer:=answer+Dist[i];
end;

Begin
  Assign(input,'poj1511.txt');
  Reset(input);
  Assign(output,'poj1511ans.txt');
  Rewrite(output);
  readln(N);
  for ii:=1 to N do
  begin
    ReadData;
    Solve;
    if ii<N then writeln(answer) else write(answer);
  end;
End.

