Const
  inf      = 'poj2394.txt';
  ouf      = 'poj2394ans.txt';
  MaxPoint = 500+10;
  QueueLen = 1000+10;
  Ondbg    = true;

  MaxCow   = 100;

Type
  road=record
         len,tgt:longint;
       end;

Var
  Edges:array[1..MaxPoint,1..MaxPoint] of road;
  EdgeNum:array[1..MaxPoint] of longint;
  Queue:array[1..QueueLen] of longint;
  Visited:array[1..MaxPoint] of boolean;
  Dist:array[1..MaxPoint] of longint;

  TSort:array[1..MaxCow] of longint;
  CowPos:array[1..MaxCow] of longint;

  F,P,C,M:longint;
  suspect:longint;

Procedure AddEdge(source,target,length:longint);
var
  num:longint;
begin
  inc(EdgeNum[source]);
  num:=EdgeNum[source];
  Edges[source,num].len:=length;
  Edges[source,num].tgt:=target;
end;

Procedure ReadData;
var
  i,pos:longint;
  src,tgr,_time:longint;   //See? those FOOLISH use "time"
begin
  fillchar(Edges,SizeOf(Edges),1);
  fillchar(EdgeNum,SizeOf(EdgeNum),0);
  fillchar(TSort,SizeOf(TSort),0);
  fillchar(CowPos,SizeOf(CowPos),0);

  readln(F,P,C,M);
  suspect:=0;
  for i:=1 to P do
  begin
    readln(src,tgr,_time);
    AddEdge(src,tgr,_time);
    AddEdge(tgr,src,_time);
  end;

  for i:=1 to C do
  begin
    readln(pos);
    CowPos[i]:=pos;
  end;
end;

Procedure SPFA(start:longint);
var
  head,tail,new,now,i:longint;
begin
  fillchar(Dist,SizeOf(Dist),1);
  fillchar(Visited,SizeOf(Visited),false);

  head:=0;
  tail:=1;
  Queue[tail]:=start;
  Dist[1]:=0;

  while head<>tail do
  begin
    inc(head);
    if head>QueueLen then head:=head-QueueLen;
    now:=Queue[head];
    Visited[now]:=false;
    for i:=1 to EdgeNum[now] do
    begin
      new:=Edges[now,i].tgt;
      if Dist[new]>Dist[now]+Edges[now,i].len then
      begin
        Dist[new]:=Dist[now]+Edges[now,i].len;
        if Visited[new]=false then
        begin
          inc(tail);
          if tail>QueueLen then tail:=tail-QueueLen;
          Visited[new]:=true;
          Queue[tail]:=new;
        end;
      end;
    end;
  end;
end;

Procedure Solve;
var
  i:integer;
begin
  SPFA(1);     //Source is the barn's position, so just need SPFA once.
  for i:=1 to C do
  begin
    if Dist[CowPos[i]]<=M then    //The cow's position is available to steal
    begin
      inc(TSort[i]);              //Use 桶排序
      inc(suspect);
    end;
  end;
end;

Procedure PrintAns;
var
  i:integer;
begin
  writeln(suspect);
  for i:=1 to C do
  begin
    if TSort[i]>0 then write(i);
    if suspect>1 then writeln;
    dec(suspect);
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
  Solve;
  PrintAns;
  Close(output);
  Close(input);
End.

