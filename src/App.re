[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";

type state =
  | LoadingDogs
  | ErrorFetchingDogs
  | LoadedDogs(array(string));

type article = {
  id: string,
  title: string,
  author: string,
  date_created: string,
};

type articlesState =
  | LoadingArticles
  | ErrorFetchingArticles
  | LoadedArticles(array(article));
//  | LoadedArticles(Js.Array.t(Js.Dict.t(Js.Json.t)));

module Decode = {
  let article = json =>
    Json.Decode.{
      id: json |> field("id", string),
      author: json |> field("author", string),
      date_created: json |> field("date_created", string),
      title: json |> field("title", string),
    };

  let articles = Json.Decode.array(article);
};

[@react.component]
let make = () => {
  let (state, setState) = React.useState(() => LoadingDogs);
  let (articlesState, setArticles) = React.useState(() => LoadingArticles);

  React.useEffect0(() => {
    let payload = Js.Dict.empty();
    Js.Dict.set(payload, "limit", Js.Json.number(10.0));
    Js.Dict.set(payload, "offset", Js.Json.number(0.0));
    Js.Promise.(
      Fetch.fetchWithInit(
        "https://blog.erl.net.ua/api/v1/post/get_available",
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
      |> then_(items => {
           let articles: array(article) =
             items |> Json.parseOrRaise |> Decode.articles;
           setArticles(_prev => LoadedArticles(articles));
           articles |> resolve;
         })
    );

    Js.Promise.(
      fetch("https://dog.ceo/api/breeds/image/random/3")
      |> then_(response => response##json())
      |> then_(jsonResponse => {
           setState(_previousState => LoadedDogs(jsonResponse##message));
           Js.Promise.resolve();
         })
      |> catch(_err => {
           setState(_previousState => ErrorFetchingDogs);
           Js.Promise.resolve();
         })
      |> ignore
    );

    // Returning None, instead of Some(() => ...), means we don't have any
    // cleanup to do before unmounting. That's not 100% true. We should
    // technically cancel the promise. Unofortunately, there's currently no
    // way to cancel a promise. Promises in general should be way less used
    // for React components; but since folks do use them, we provide such an
    // example here. In reality, this fetch should just be a plain callback,
    // with a cancellation API
    None;
  });

  <Container>
    <div
      style={ReactDOMRe.Style.make(
        ~height="120px",
        ~display="flex",
        ~alignItems="center",
        ~justifyContent="center",
        (),
      )}>
      {switch (state) {
       | ErrorFetchingDogs => React.string("An error occurred!")
       | LoadingDogs => React.string("Loading...")
       | LoadedDogs(dogs) =>
         dogs
         ->Belt.Array.mapWithIndex((i, dog) => {
             let imageStyle =
               ReactDOMRe.Style.make(
                 ~height="120px",
                 ~width="100%",
                 ~marginRight=i === Js.Array.length(dogs) - 1 ? "0px" : "8px",
                 ~borderRadius="8px",
                 ~boxShadow="0px 4px 16px rgb(200, 200, 200)",
                 ~backgroundSize="cover",
                 ~backgroundImage={j|url($dog)|j},
                 ~backgroundPosition="center",
                 (),
               );
             <div key=dog style=imageStyle />;
           })
         ->React.array
       }}
    </div>
  </Container>;
};