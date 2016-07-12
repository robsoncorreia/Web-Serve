function startup()
print('in startup')
dofile('controle.lua')
end

tmr.alarm(0,5000,0,startup)
