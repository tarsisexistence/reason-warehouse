type articleState =
  | LoadingArticle
  | ErrorFetchingArticle
  | LoadedArticle(Types.article);

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
           let article: Types.article =
             article |> Json.parseOrRaise |> Utils.DecodeArticles.article;
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
      <p> {article |> Utils.Common.getTimeDescription |> React.string} </p>
    </article>
  };
};