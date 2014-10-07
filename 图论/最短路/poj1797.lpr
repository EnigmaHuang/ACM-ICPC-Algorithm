Const
  inf = 'poj1797.txt';
  ouf = 'poj1797ans.txt';
  MaxPointNum = 1000;
  QueueLength = 2000;
  OnDebug     = true;

Type
  {
  EdgePtr=^Edge;
  Edge = record
           src,tgr,ld:longint;
           next:EdgePtr;
         end;
  }
  TEdgeArray=array[1..MaxPointNum,1..MaxPointNum] of longint;

Var
  Edges:TEdgeArray;
  Link:array[1..MaxPointNum,0..MaxPointNum] of longint;
  Queue:array[1..QueueLength] of longint;
  Visited:array[1..MaxPointNum] of boolean;
  MaxLoad:array[1..MaxPointNum] of longint;

  k,m,n,ii:longint;

Function Min(a,b:longint):longint;
begin
  if a<b then exit(a) else exit(b);
end;

{
Procedure FreeMemory(var Edges:TEdgeArray);
var
  i:longint;
  p1,p2:EdgePtr;
begin
  for i:=1 to n do
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
}

Procedure AddEdge(var Edges:TEdgeArray;source,target,load:longint);
{var
  p:EdgePtr;
}
begin
  {
  New(p);
  p^.next:=Edges[source];
  p^.src :=source;
  p^.tgr :=target;
  p^.ld  :=load;
  Edges[source]:=p;
  }
  Edges[source,target]:=load;
  inc(Link[source,0]);
  Link[source,Link[source,0]]:=target;
end;

Procedure ReadData;
var
  i,source,target,load:longint;
begin
  fillchar(Edges,SizeOf(Edges),1);
  fillchar(Link,SizeOf(Link),0);
  readln(n,m);
  for i:=1 to n do Edges[i,i]:=0;
  for i:=1 to m do
  begin
    readln(source,target,load);
    AddEdge(Edges,source,target,load);
    AddEdge(Edges,target,source,load);
  end;
end;

Procedure SPFA(start:longint);
var
  head,tail:longint;
  i,j,now,new:longint;
  {p:EdgePtr;}
begin
  fillchar(Visited,sizeof(Visited),false);
  fillchar(MaxLoad,SizeOf(MaxLoad),0);       //一开始的初始载重应该设为0

  MaxLoad[start]:=maxlongint;                //出发点到自己无限载，这样下面才能对
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
    {p:=Edges[now];          //同一出发点，取队头元素(第一条边)开始枚举
    if p=nil then continue;
    repeat
      new:=p^.tgr;     }
    for i:=1 to Link[now,0] do
    begin
      new:=Link[now,i];
      if MaxLoad[new]<min(MaxLoad[now],Edges[now,new]) then
      begin
        MaxLoad[new]:=min(MaxLoad[now],Edges[now,new]);
        if Visited[new]=false then
        begin
          tail:=tail+1;
          if tail>QueueLength then tail:=tail-QueueLength;
          Queue[tail]:=new;
          Visited[new]:=true;
        end;
      end;
    end;
    {  p:=p^.next;           //取下一条边
    until p=nil;    }
  end;
  {FreeMemory(Edges);  }
end;

Procedure PrintAnswer(index:longint);
begin
  writeln('Scenario #',index,':');
  writeln(MaxLoad[n]);
  if index<k then writeln;
end;

Begin
  if OnDebug then
  begin
    Assign(input,inf);
    Reset(input);
    Assign(output,ouf);
    Rewrite(output);
  end;
  readln(k);
  for ii:=1 to k do
  begin
    ReadData;
    SPFA(1);
    PrintAnswer(ii);
  end;
End.

