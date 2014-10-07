Const
  MaxNode = 26;
  MaxEdge = 1005;
  inf     = 'poj2337.txt';
  ouf     = 'poj2337ans.txt';
  Ondbg   = true;

Type
  TEdge = record
            v,next,wid:integer;
          end;

Var
  e:array[1..MaxEdge] of TEdge;
  f:array[1..MaxNode] of integer;
  h:array[1..MaxNode] of integer;
  ans:array[1..MaxEdge] of integer;
  words:array[0..MaxEdge] of string;
  ind,oud:array[1..MaxNode] of integer;
  rank:array[1..MaxNode] of integer;
  vis:array[1..MaxEdge] of boolean;
  pos,index:integer;

  t,n,source,StartEdge:integer;

Function Root(x:integer):integer;
begin
  if f[x]<>x then f[x]:=Root(f[x]);
  exit(f[x]);
end;

Procedure Union(a,b:integer);
var
  fa,fb:integer;
begin
  fa:=Root(a);
  fb:=Root(b);
  if fa=fb then exit;
  if rank[fa]=rank[fb] then inc(rank[fa]);
  if rank[fa]>rank[fb] then f[fb]:=fa else f[fa]:=f[fb];
end;

Function CheckOK:boolean;
var
  i,ic,oc,maxsg:integer;
  hasans:boolean;
begin
  source:=0;
  StartEdge:=0;
  ic:=0;
  oc:=0;
  for i:=1 to MaxNode do
  begin
    if abs(ind[i]-oud[i])>1 then exit(false);  //出入度之差大于1，直接退出
    if oud[i]-ind[i]=1 then
    begin
      source:=i;
      inc(oc);
    end;
    if oud[i]-ind[i]=-1 then inc(ic);
  end;

  if source=0 then
  begin
    for i:=1 to MaxNode do if (ind[i]>0) or (oud[i]>0) then break;
    source:=i;
  end;

  if (ic=0) and (oc=0) then hasans:=true else hasans:=false;
  if (ic>1) or (oc>1) or (ic<>oc) then exit(false);  //出入度之差为+-1的点应该各有一个
  maxsg:=0;
  //求极大连通子图数，以确定全图连通性
  for i:=1 to MaxNode do if (i=Root(i)) and ((ind[i]>0) or (oud[i]>0)) then inc(maxsg);
  if maxsg>1 then exit(false);

  StartEdge:=h[source];
end;

Procedure AddEdge(src,trg,id:integer);
var
  tmp,u,v,swap:integer;
begin
  inc(index);
  with e[index] do
  begin
    v:=trg;
    wid:=id;
    next:=h[src];
  end;
  h[src]:=index;
  inc(oud[src]);
  inc(ind[trg]);
  Union(src,trg);

  tmp:=h[src];
  while (e[tmp].next<>-1) do
  begin
    u:=e[tmp].wid;
    v:=e[e[tmp].next].wid;
    if words[u]>words[v] then
    begin
      swap:=e[tmp].v;
      e[tmp].v:=e[e[tmp].next].v;
      e[e[tmp].next].v:=swap;
      swap:=e[tmp].wid;
      e[tmp].wid:=e[e[tmp].next].wid;
      e[e[tmp].next].wid:=swap;
    end;
    tmp:=e[tmp].next;
  end;
end;

Procedure ReadData;
var
  i,u,v:integer;
  txt:text;
begin
  fillchar(h,sizeof(h),-1);
  fillchar(oud,sizeof(oud),0);
  fillchar(ind,sizeof(ind),0);
  fillchar(rank,sizeof(rank),0);
  fillchar(vis,sizeof(vis),false);
  for i:=1 to MaxNode do f[i]:=i;
  index:=0;

  readln(n);
  for i:=1 to n do readln(words[i]);
  for i:=1 to n do
  begin
    u:=Ord(words[i][1])-Ord('a')+1;
    v:=Ord(words[i][length(words[i])])-Ord('a')+1;
    AddEdge(u,v,i);
  end;
end;

Procedure Euler(nowp,nowe:integer);
var
  i:integer;
begin
  vis[nowe]:=true;
  i:=h[nowp];
  while i<>-1 do
  begin
    if vis[i]=false then Euler(e[i].v,i);
    i:=e[i].next;
  end;
  inc(pos);
  ans[pos]:=nowe;
end;

Procedure Solve;
begin
  pos:=1;
  if CheckOK then
  begin
    dec(pos);
    Euler(e[StartEdge].v,StartEdge);
  end
  else ans[pos]:=0;
end;

Procedure Print;
var
  i:integer;
begin
  for i:=pos downto 1 do
  begin
    write(words[e[ans[i]].wid]); //注意数组嵌套关系…………
    if i>1 then write('.');
  end;
  writeln;
end;

Begin
  if Ondbg then
  begin
    Assign(input,inf);Reset(input);
    Assign(output,ouf);Rewrite(output);
  end;

  words[0]:='***';
  readln(t);
  repeat
    ReadData;
    Solve;
    Print;
    dec(t);
  until t=0;

  if Ondbg then
  begin
    Close(input);Close(output);
  end;
End.
