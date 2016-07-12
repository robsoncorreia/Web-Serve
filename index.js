$(document).ready(function () {
    //:::::::::::::::::::::::::::::::::::ANIMAÇÃO DA SETA PARA CIMA::::::::::::::::::::::::::::::::::::::::::
    function loop() {
        $("#p_go_top").animate({ 'bottom': '0' }, {
            duration: 500,
            complete: function () {
                $("#p_go_top").animate({ 'bottom': '10' }, {
                    duration: 500,
                    complete: loop
                });
            }
        });
    }
    loop();
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    $("#p_go_top").click(function () {
        fechar_menu();
        contador_menu = 3;
    })
    //::::::::::::::::::::::::::::::::::::::::::SEM REFRESH::::::::::::::::::::::::::::::::::::::::::::::::::
    $("a").click(function (event) {
        event.preventDefault();
        var href = $(this).attr('href');
        $("#div_false").load(href);
    });
    //::::::::::::::::::::::::::::::::::::::::::CONSTANTE::::::::::::::::::::::::::::::::::::::::::::::::::::
    $("#p_go_top").transition({ scale: 0, delay: 500 });
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    function ShowH1Menu() {
        setTimeout(function () {
            $("#h1_sistema").css({ "top": "552px" });
            $("#h1_sistema").fadeIn(200);
            GirarH1();
            $("#h1_sistema").fadeOut(200);
        }, 3000);
    }
    function ShowH1Menu2() {
        setTimeout(function () {
            $("#h1_sistema").css({ "top": "-20px" });
            $("#h1_sistema").fadeIn(200);
            GirarH1();
            $("#h1_sistema").fadeOut(200);
        }, 3000);
    }
    //::::::::::::::::::::::::::::::::::::::::::QUARTO:::::::::::::::::::::::::::::::::::::::::::::::::::::::
    var quarto_desligado = "http://192.168.1.2/?pin=DESLIGA1";
    var quarto_ligado = "http://192.168.1.2/?pin=LIGA1";
    var contador_quarto = 1;
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    $("#botao_quarto").click(function () {
        if (contador_quarto >= 3) {
            contador_quarto = 1;
        }
        contador_quarto += 1;
        if (contador_quarto == 2) {
            desligar_quarto();
        }
        if (contador_quarto == 3) {
            ligar_quarto(); 
        }
    });
    //.......................................................................................................
    function ligar_quarto() {
        $("#a_quarto").attr('href', quarto_ligado);
        $("#botao_quarto").css({ 'background-color': 'rgba(35, 157, 27, 1)' });
        $("#botao_quarto").transition({ scale: 1 });
        animacao_menu();
    }
    function desligar_quarto() {
        $("#a_quarto").attr('href', quarto_desligado);
        $("#botao_quarto").css({ 'background-color': 'rgba(142, 31, 31, 1)' });
        $("#botao_quarto").transition({ scale: 0.95 });
        animacao_menu();
    }   
    //::::::::::::::::::::::::::::::::::::::::::SALA::::::::::::::::::::::::::::::::::::::::::::::::::::::
    var sala_desligada = "http://192.168.1.2/?pin=LIGA2";
    var sala_ligado = "http://192.168.1.2/?pin=DESLIGA2";
    var contador_sala = 1;
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    function ligar_sala() {
        $("#a_sala").attr('href', sala_ligado);
        $("#botao_sala").css({ 'background-color': 'rgba(35, 157, 27, 1)' });
        $("#botao_sala").transition({ scale: 1 });
        animacao_menu();
    }
    function desligar_sala() {
        $("#a_sala").attr('href', sala_desligada);
        $("#botao_sala").css({ 'background-color': 'rgba(142, 31, 31, 1)' });
        $("#botao_sala").transition({ scale: 0.95 });
        animacao_menu();
    }
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    $("#botao_sala").click(function () {
        if (contador_sala >= 3) {
            contador_sala = 1;
        }
        contador_sala += 1;
        if (contador_sala == 2) {
            desligar_sala();
        }
        if (contador_sala == 3) {
            ligar_sala();
        }
    });
    //::::::::::::::::::::::::::::::::::::::::::BOTÃO TIMER::::::::::::::::::::::::::::::::::::::::::::::::::
    var timer_ligado = "http://192.168.1.20/timer_l";
    var timer_desligado = "http://192.168.1.20/timer_d";
    var contador_timer = 1;
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    function ligar_timer() {
        $("#a_timer").attr('href', timer_ligado);
        $("#botao_timer").css({ 'background-color': 'rgba(35, 157, 27, 1)' });
        $("#botao_timer").transition({ scale: 1 });
    }
    function desligar_timer() {
        $("#a_timer").attr('href', timer_desligado);
        $("#botao_timer").css({ 'background-color': 'rgba(142, 31, 31, 1)' });
        $("#botao_timer").transition({ scale: 0.95 });
    }
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    $("#botao_timer").click(function () {
        if (contador_timer >= 3) {
            contador_timer = 1;
        }
        contador_timer += 1;
        if (contador_timer == 2) {
            desligar_timer();
        }
        if (contador_timer == 3) {
            ligar_timer();
        }
        
    });
    //::::::::::::::::::::::::::::::::::::::::::BOTÃO TODOS	:::::::::::::::::::::::::::::::::::::::::::::::::::
    var todos_ligado = "http://192.168.1.2/?pin=LIGA3";
    var todos_desligado = "http://192.168.1.2/?pin=DESLIGA3";
    var contador_todos = 1;
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    function ligar_todos() {
        $("#a_todos").attr('href', todos_desligado);
        $("#botao_todos").css({ 'background-color': 'rgba(35, 157, 27, 1)' });
        $("#botao_todos").transition({ scale: 1 });

    }
    function desligar_todos() {
        $("#a_todos").attr('href', todos_ligado);
        $("#botao_todos").css({ 'background-color': 'rgba(142, 31, 31, 1)' });
        $("#botao_todos").transition({ scale: 0.95 });
    }
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    $("#botao_todos").click(function () {
        if (contador_todos >= 3) {
            contador_todos = 1;
        }
        contador_todos += 1;
        if (contador_todos == 2) {
            desligar_todos();
        }
        if (contador_todos == 3) {
            ligar_todos();
        }
    });
    //::::::::::::::::::::::::::::::::::::::::::MENU:::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    var contador_menu = 1;
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    function fechar_menu() {
        $("#h1_sistema").hide();
        ShowH1Menu2()
        $("#menu").animate({ height: '590px' }, 200).add($("#grade_sistema_tudo").fadeOut(200));
        $("html, body").animate({ scrollTop: 0 }, '2000', 'swing');
        $("#p_go_top").transition({ scale: 0, delay: 500 });
    }
    function abrir_menu() {
        $("#h1_sistema").hide();
        ShowH1Menu();
        $("#menu").animate({ height: '1152px' }, 200).add($("#grade_sistema_tudo").fadeIn(200));
        $("html, body").animate({ scrollTop: 590 }, '2000', 'swing');
        $("#p_go_top").transition({ scale: 1.1, delay: 500 });
    }
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    $("#div_menu").click(function () {
        animacao_menu();
        if (contador_menu >= 3) {
            contador_menu = 1;
        }
        contador_menu += 1;
        if (contador_menu == 2) {
            abrir_menu();
        }
        if (contador_menu == 3) {
            fechar_menu();
        }
    });
    //::::::::::::::::::::::::::::::::::::::::::ANIMAÇÃO DO MENU::::::::::::::::::::::::::::::::::::::::::::::
    function animacao_menu() {
        $("#um").animate({ width: 46 }, 200).animate({ width: 60 }, 200).animate({ width: 46 }, 200);
        $("#dois").delay(200).animate({ width: 46 }, 200).animate({ width: 60 }, 400).animate({ width: 46 }, 200);
        $("#tres").delay(400).animate({ width: 46 }, 200).animate({ width: 60 }, 400).animate({ width: 46 }, 200);
    }
    function GirarH1() {
        $("#h1_sistema").transition({
            perspective: '300px',
            rotate3d: '1,0,0,360deg'
        }, 2000);
        $("#h1_sistema").transition({
            perspective: '300px',
            rotate3d: '1,0,0,0deg'
        }, 2000);
    }
    for (var i = 0; i < 1; i++) {
        animacao_menu();
        GirarH1();
    }
});

