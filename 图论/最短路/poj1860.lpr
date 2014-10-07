Const
  inf = 'poj1860.txt';
  ouf = 'poj1860ans.txt';
  MaxPointNum = 100;
  QueueLength = 200;
  OnDebug = true;

Var
  Link:array[1..MaxPointNum,0..MaxPointNum] of longint;
  Cost,Rate:array[1..MaxPointNum,1..MaxPointNum] of double;
  Dist:array[1..MaxPointNum] of double;
  Visited:array[1..MaxPointNum] of boolean;
  Queue:array[1..QueueLength] of longint;
  Visit:array[1..MaxPointNum] of longint;

  N,M,start:longint;
  total:double;

Procedure ReadData;
var
  i,A,B:longint;
  cst,rte:double;
begin
  readln(N,M,start,total);
  for i:=1 to m do
  begin
    read(A,B);

    inc(Link[A,0]);
    Link[A,Link[A,0]]:=B;

    inc(Link[B,0]);
    Link[B,Link[B,0]]:=A;

    read(rte,cst);
    Rate[A,Link[A,0]]:=rte;
    Cost[A,Link[A,0]]:=cst;

    read(rte,cst);
    Rate[B,Link[B,0]]:=rte;
    Cost[B,Link[B,0]]:=cst;
  end;
end;

Function SPFA:boolean;
var
  head,tail,now,new,i:longint;
begin
  fillchar(Visited,SizeOf(Visited),false);
  fillchar(Visit,SizeOf(Visit),0);
  fillchar(Dist,SizeOf(Dist),0);

  Dist[start]:=total;
  head:=-1;
  tail:=0;
  Visited[start]:=true;
  Queue[tail]:=start;

  while head<>tail do
  begin
    inc(head);
    if head>QueueLength then head:=head-QueueLength;
    now:=Queue[head];
    Visited[now]:=false;

    for i:=1 to Link[now,0] do
    begin
      new:=Link[now,i];
      if (Dist[now]-Cost[now,i])*Rate[now,i]>Dist[new] then
      begin
        Dist[new]:=(Dist[now]-Cost[now,i])*Rate[now,i];
        //if Dist[start]>total then exit(true);
        if not Visited[new] then
        begin
          Visited[new]:=true;
          inc(tail);
          if tail>QueueLength then tail:=tail-QueueLength;
          Queue[tail]:=new;

          inc(Visit[Link[now,i]]);
          if Visit[Link[now,i]]=n then exit(true);

        end;
      end;
    end;
  end;
  exit(false);
end;

Begin
  if OnDebug then
  begin
    Assign(input,inf);
    Reset(input);
    Assign(output,ouf);
    Rewrite(output);
  end;

  ReadData;
  if SPFA then write('YES')
          else write('NO');

  Close(input);
  Close(output);
End.
