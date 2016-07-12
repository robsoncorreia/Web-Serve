-- Programa: Web Server com ESP8266 Nodemcu
-- Autor: FILIPEFLOP
 
-- Conexao na rede Wifi
wifi.setmode(wifi.STATION)
wifi.sta.config("##########","###########")
print(wifi.sta.getip())
-- Definicoes do Web Server
srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
    conn:on("receive", function(client,request)
        local buf = "";
        local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP");
        if(method == nil)then
            _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP");
        end
        local _GET = {}
        if (vars ~= nil)then
            for k, v in string.gmatch(vars, "(%w+)=(%w+)&*") do
                _GET[k] = v
            end
        end
        buf = buf.."<h2>Quarto</h2>";
        buf = buf.."<p><a href=\"?pin=LIGA1\"><button><b>Liga</b></button></a> <br/><br/><a href=\"?pin=DESLIGA1\"><button><b>Desliga</b></button></a></p>";
            local _on,_off = "",""
        if(_GET.pin == "LIGA1")then
            print('a');
        elseif(_GET.pin == "DESLIGA1")then
            print('b');
        elseif(_GET.pin == "LIGA2")then
            print('c');
        elseif(_GET.pin == "DESLIGA2")then
            print('d');
		elseif(_GET.pin == "LIGA3")then
            print('e');
        elseif(_GET.pin == "DESLIGA3")then
            print('f');
        elseif(_GET.pin == "TV")then
            print('g');
        end
        client:send(buf);
        client:close();
        collectgarbage();
    end)
end)
