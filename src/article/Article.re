let getTimeDescription = (article: Typings.article) => {
  let date = Js.Date.fromString(article.date_created);
  let month =
    date |> Js.Date.getMonth |> int_of_float |> Utils.Common.getMonthName;
  let day = date |> Js.Date.getDate;
  let year = date |> Js.Date.getFullYear;
  let readingTime = (article.timing |> Js.Int.toFloat) /. 60.0 |> Js.Math.ceil;
  {j|$month $day, $year • $readingTime min read|j};
};

type articleState =
  | LoadingArticle
  | ErrorFetchingArticle
  | LoadedArticle(Typings.article);

[@react.component]
let make = (~id: string) => {
  let (state, setState) = React.useState(() => LoadingArticle);

  React.useEffect0(() => {
    let payload = Js.Dict.empty();
    Js.Dict.set(payload, "id", Js.Json.string(id));
    Js.Promise.(
      Fetch.fetchWithInit(
        "https://blog.erl.net.ua/api/v1/post/get",
        Fetch.RequestInit.make(
          ~method_=Post,
          ~body=
            Fetch.BodyInit.make(
              Js.Json.stringify(Js.Json.object_(payload)),
            ),
          ~headers=
            Fetch.HeadersInit.make({"Content-Type": "application/json"}),
          (),
        ),
      )
      |> then_(Fetch.Response.text)
      |> then_(article => {
           let article: Typings.article =
             article |> Json.parseOrRaise |> Utils.DecodeArticle.article;
           setState(_prev => LoadedArticle(article));
           article |> resolve;
         })
      |> ignore
    );

    None;
  });

  switch (state) {
  | ErrorFetchingArticle => "An error occurred!" |> React.string
  | LoadingArticle => "Loading..." |> React.string
  | LoadedArticle(article) =>
    <article>
      <p
        style={ReactDOMRe.Style.make(
          ~fontSize="1.75rem",
          ~fontWeight="700",
          ~margin="0",
          (),
        )}>
        {article.title |> React.string}
      </p>
      <p> {article |> getTimeDescription |> React.string} </p>
      <p> {article.data |> React.string} </p>
    </article>
  };
};