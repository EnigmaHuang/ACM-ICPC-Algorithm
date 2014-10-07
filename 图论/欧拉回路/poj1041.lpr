Const
  MaxNode = 50;
  MaxEdge = 2000;
  inf     = 'poj1041.txt';
  ouf     = 'poj1041ans.txt';
  Ondbg   = true;

Type
  TEdge = record
            u,v:integer;
          end;

Var
  d:array[1..MaxNode] of integer;      //入度
  e:array[1..MaxEdge] of TEdge;        //边集
  vis:array[1..MaxEdge] of boolean;    //边的访问标记
  ans:array[1..MaxEdge] of integer;    //答案

  EdgeNum,start,top,MaxID,x,y,z,k:integer;

Function Max(a,b:integer):integer;
begin
  if a>b then exit(a) else exit(b);
end;

Function Min(a,b:integer):integer;
begin
  if a<b then exit(a) else exit(b);
end;

Function HasOddDegree:boolean;
var
  i:integer;
begin
  HasOddDegree:=false;
  for i:=1 to MaxID do if Odd(d[i]) then exit(true);
end;

Procedure Euler(now:integer);
var
  i:integer;
begin
  for i:=1 to EdgeNum do
  begin
    if (vis[i]=false) and ((e[i].u=now) or (e[i].v=now)) then
    begin
      vis[i]:=true;
      Euler(e[i].u+e[i].v-now);
      inc(top);
      ans[top]:=i;
    end;
  end;
end;

Begin
  if Ondbg then
  begin
    Assign(input,inf);Reset(input);
    Assign(output,ouf);Rewrite(output);
  end;

  read(x,y);
  while not ((x=0) and (y=0)) do
  begin
    fillchar(e,sizeof(e),0);
    fillchar(d,sizeof(d),0);
    fillchar(vis,sizeof(vis),false);
    MaxID:=0;
    edgenum:=0;
    top:=0;
    start:=Min(x,y);  //起点为第一组输入数据中最小的交点
    repeat
      readln(z);
      e[z].u:=x;
      e[z].v:=y;
      inc(d[x]);
      inc(d[y]);
      inc(EdgeNum);
      MaxID:=Max(MaxID,Max(x,y));
      read(x,y);
    until (x=0) and (y=0);
    if HasOddDegree then writeln('Round trip does not exist.')
    else
    begin
      Euler(start);
      for k:=top downto 1 do write(ans[k],' ');
      writeln;
    end;
    read(x,y);
  end;

  if Ondbg then
  begin
    Close(input);Close(output);
  end;
End.
