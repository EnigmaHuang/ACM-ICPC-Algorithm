Const
  MaxNode = 26;
  inf     = 'poj1386.txt';
  ouf     = 'poj1386ans.txt';
  Ondbg   = true;

Var
  ind,oud,father:array[1..MaxNode] of longint;
  vis:array[1..MaxNode] of boolean;
  rank:array[1..MaxNode] of longint;

  t:integer;

Function Root(x:longint):longint;
var
  i:integer;
begin
  if father[x]<>x then father[x]:=Root(father[x]);
  exit(father[x]);
end;

Procedure Union(h,t:longint);
var
  f1,f2:longint;
begin
  f1:=Root(h);
  f2:=Root(t);
  if rank[f1]=rank[f2] then inc(rank[f1]);
  if rank[f1]>rank[f2] then father[f2]:=f1 else father[f1]:=f2;
end;

Function CanLink(a,b:longint):boolean;
var
  d1,d2:longint;
begin
  d1:=ind[a]-oud[a];
  d2:=ind[b]-oud[b];
  if ((d1=1) and (d2=-1)) or ((d1=-1) and (d2=1)) then exit(true)
                                                  else exit(false);
end;

Procedure ReadData;
var
  s:string;
  h,t,n,i:longint;
begin
  fillchar(ind,sizeof(ind),0);
  fillchar(oud,sizeof(oud),0);
  fillchar(vis,sizeof(vis),false);
  fillchar(rank,sizeof(rank),0);
  for i:=1 to MaxNode do father[i]:=i;
  readln(n);
  for i:=1 to n do
  begin
    readln(s);
    h:=Ord(s[1])-Ord('a')+1;
    t:=Ord(s[length(s)])-Ord('a')+1;
    inc(ind[t]);
    inc(oud[h]);
    vis[t]:=true;
    vis[h]:=true;
    Union(h,t);
  end;
end;

Procedure Solve;
var
  i,j,x,odd1,odd2,notsuit:longint;
  hasans:boolean;
begin
  odd1:=0;
  odd2:=0;
  notsuit:=0;
  hasans:=true;

  for i:=1 to MaxNode do if vis[i] then break;
  x:=i;  //随便找一个点
  x:=Root(x);
  for i:=1 to MaxNode do if vis[i] then
  begin
    if ind[i]<>oud[i] then   //出度与入度不同
    begin
      inc(notsuit);
      //如果存在的话，则记录两个出入度不相等的点
      if odd1=0 then odd1:=i
      else if odd2=0 then odd2:=i
      else  //有三个或以上的点出度与入度的数目不一致，直接判定不可行
      begin
        hasans:=false;
        break;
      end;
    end;
    if Root(i)<>x then  //如果有点不连通，直接判定不可行
    begin
      hasans:=false;
      break;
    end;
  end;
  if hasans and (notsuit=0) then writeln('Ordering is possible.')
  else if hasans and (notsuit=2) and CanLink(odd1,odd2) then writeln('Ordering is possible.')
  else writeln('The door cannot be opened.');
end;

Begin
  if Ondbg then
  begin
    Assign(input,inf);Reset(input);
    Assign(output,ouf);Rewrite(output);
  end;

  readln(t);
  while t>0 do
  begin
    ReadData;
    Solve;
    dec(t);
  end;

  if Ondbg then
  begin
    Close(input);Close(output);
  end;
End.
