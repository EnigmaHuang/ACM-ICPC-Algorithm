const
  maxn=230;

var
  g:array[-1..maxn,1..4]of record
      n,v:integer;
    end;
  d,xu,num,a:array[-1..maxn]of integer;
  ans:integer;
  x,n,casen,o,i:integer;
  flag:boolean;

procedure add(a,b,c:integer);
begin
  inc(num[a]);
  g[a,num[a]].n:=b;
  g[a,num[a]].v:=c;
end;

procedure init;
var 
  i:integer;
begin
  fillchar(g,sizeof(g),0);
  add(-1,23,ans);   //原程序没有加这条边
  for i:=0 to 23 do 
  begin
    if i<=7  then add(i+16,i,xu[i]-ans)
             else add(i-8,i,xu[i]);
    add(i-1,i,0);
    add(i,i-1,-a[i]);
  end;
end;

function bellman_ford:boolean;
var 
  i,j,k:integer;
  ff:boolean;
begin
  bellman_ford:=false;
  fillchar(d,sizeof(d),0);
  for i:=0 to 23 do 
  begin
    ff:=true;
    for j:=-1 to 23 do
      for k:=1 to num[j] do
        if d[j]+g[j,k].v>d[g[j,k].n] then 
	    begin
          d[g[j,k].n]:=d[j]+g[j,k].v;
		  ff:=false;
        end;
    if ff then break;
  end;
	
  for j:=0 to 23 do if d[j]-d[j-1]>a[j] then exit;
  for j:=-1 to 23 do
    for k:=1 to num[j] do
      if d[j]+g[j,k].v>d[g[j,k].n] then exit;
    
  bellman_ford:=(d[23]=ans); //这句，是判断d[23]-d[-1]是否就是ans,直接返回true也能AC,可见数据不是很强。
end;

begin
  readln(casen);
  for o:=1 to casen do begin
    for i:=0 to 23 do read(xu[i]);readln;readln(n);
    for i:=1 to n do begin read(x);inc(a[x]);end;
    flag:=false;
    for ans:=0 to n do begin
      fillchar(d,sizeof(d),0);
      fillchar(num,sizeof(num),0);
      init;
      if bellman_ford then begin
        flag:=true;
        break;
      end;
    end;
    if flag then writeln(ans) else writeln('No Solution');
  end;
end.